#include "NetworkWorker.h"
#include <QVector>
#include <QTime>
#include <QMutexLocker>
#include "src/common/GameTimer.h"
#include "easylogging++.h"
#include <cassert>

namespace net {

NetworkWorker::NetworkWorker(quint8 client_id, QHostAddress address, quint16 server_port, quint16 local_port, std::shared_ptr<GameTimer> game_timer)
  : last_event_id_(0), // the first class to GetNextEventId will return 1 (intended)
    last_packet_id_(0), // idem with GetNextPacketId
    client_id_(client_id),
    timer_(this),
    ping_timer_(this),
    clean_ping_data_timer_(this),
    game_timer_(game_timer) {

  socket_.connectToHost(address, server_port);

  connect(&timer_, SIGNAL(timeout()), this, SLOT(SendPendingEvents()));
  connect(&ping_timer_, SIGNAL(timeout()), this, SLOT(SendPingPacket()));
  connect(&clean_ping_data_timer_, SIGNAL(timeout()), this, SLOT(CleanPingData()));
  timer_.start(100);
  ping_timer_.start(200);
  clean_ping_data_timer_.start(5000);

  connect(&receive_socket_, SIGNAL(readyRead()), this, SLOT(ReadPendingDatagrams()));
  connect(&receive_socket_, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(SocketError(QAbstractSocket::SocketError)));
  receive_socket_.bind(local_port);

  LOG(INFO) << "Initialized the client network worker: listening on " << local_port << ", connected to " << address.toString().toStdWString() << ":" << server_port;
}

void NetworkWorker::SocketError(QAbstractSocket::SocketError) {
  LOG(ERROR) << "Socket error: " << socket_.errorString().toStdWString();
}

quint32 NetworkWorker::GetNextEventId() {
  last_event_id_ += 1;
  return last_event_id_;
}

quint32 NetworkWorker::GetNextPacketId() {
  last_packet_id_ += 1;
  return last_packet_id_;
}

void NetworkWorker::ReadPendingDatagrams() {
  VLOG(9) << "Reading pending datagrams...";
  while(receive_socket_.hasPendingDatagrams()) {
    QByteArray datagram;
    datagram.resize(receive_socket_.pendingDatagramSize());
    QHostAddress sender;
    quint16 sender_port;
    receive_socket_.readDatagram(datagram.data(), datagram.size(), &sender, &sender_port);
    ProcessDatagram(datagram);
  }

}

void NetworkWorker::ProcessDatagram(const QByteArray& datagram) {
  VLOG(LOG_PACKET_LEVEL) << "Received a datagram";
  QDataStream stream(datagram);
  if(!CheckProtocolAndVersion(stream)) {
    LOG(WARNING) << "Protocol or version ID mismatch, dropping datagram.";
    return;
  }
  quint32 packet_id = GetPacketId(stream);
  if(!CheckStreamStatus(stream)) {
    LOG(WARNING) << "Could not deserialize the packet ID";
    return;
  }
  VLOG(LOG_PACKET_LEVEL) << "Received datagram packet id: " << packet_id;
  quint8 packet_type = GetPacketType(stream);
  if(!CheckStreamStatus(stream)) {
    LOG(WARNING) << "Could not deserialize the packet type.";
    return;
  }
  switch(packet_type) {
    case kPingPacketId:
      VLOG(LOG_PACKET_LEVEL) << "The datagram is a ping packet.";
      ProcessPingPacket(stream);
      break;
    default:
      LOG(WARNING) << "Received unknown packet type " << packet_type << ", dropping datagram.";
      break;
  }
}

bool NetworkWorker::CheckProtocolAndVersion(QDataStream &stream) {
  assert(stream.status() == QDataStream::Ok);
  quint8 protocol_id;
  quint8 server_version;
  stream >> protocol_id;
  stream >> server_version;
  if(!CheckStreamStatus(stream)) {
    LOG(WARNING) << "Could not deserialize the protocol ID or version.";
    return false;
  }
  quint8 accepted_version = NetworkWorker::kClientVersion;
  quint8 accepted_protocol_id = NetworkWorker::kProtocolId;
  if(protocol_id != accepted_protocol_id) {
    LOG(WARNING) << "Received unexpected protocol ID: got " << protocol_id << ", expected " << accepted_protocol_id;
    return false;
  }
  if(server_version != accepted_version) {
    LOG(WARNING) << "Received unsupported server version: got " << server_version << ", but only version " << accepted_version << " is supported by this client.";
    return false;
  }
  return true;
}

void NetworkWorker::ProcessPingPacket(QDataStream& stream) {
  assert(stream.status() == QDataStream::Ok);
  quint32 packet_id;
  quint32 server_timestamp;
  stream >> packet_id;
  stream >> server_timestamp; // unused for now
  if(!CheckStreamStatus(stream)) {
    LOG(WARNING) << "Could not deserialize the ping packet contents.";
    return;
  }
  auto send_timestamp = ping_timestamps_.find(packet_id);
  if(send_timestamp == ping_timestamps_.end()) {
    LOG(WARNING) << "Received a ping response, but could not find when the question was sent.";
  } else {
    UpdateRoundTripTime(send_timestamp->second);
    // even if the line below is not called (exception), the CleanPingData
    // method will prevent the memory leak
    ping_timestamps_.erase(send_timestamp);
  }
}

void NetworkWorker::UpdateRoundTripTime(quint32 send_timestamp) {
  quint32 now = game_timer_->GetTimestamp();
  if(now < send_timestamp) {
    LOG(ERROR) << "The timestamp of a sent ping packet is in the future. This probably means the client clock settings changed after the packet was sent.";
    return;
  }
  round_trip_time_ = (double)round_trip_time_ * 0.9 + ((double)now - (double)send_timestamp) * 0.1;
  emit Latency(round_trip_time_ / 2);
}

quint8 NetworkWorker::GetPacketType(QDataStream& stream) {
  assert(stream.status() == QDataStream::Ok);
  quint8 packet_id;
  stream >> packet_id;
  return packet_id;
}

quint32 NetworkWorker::GetPacketId(QDataStream& stream) {
  assert(stream.status() == QDataStream::Ok);
  quint32 packet_id;
  stream >> packet_id;
  return packet_id;
}

void NetworkWorker::SendPingPacket() {
  QByteArray buffer;
  QDataStream stream(&buffer, QIODevice::OpenModeFlag::WriteOnly);
  quint32 id = PrepareHeader(stream, kPingPacketId);
  ping_timestamps_[id] = game_timer_->GetTimestamp();
  stream << ping_timestamps_[id];
  assert(stream.status() == QDataStream::Status::Ok);
  socket_.write(buffer);
  VLOG(9) << "Ping packet sent / timestamp = " << ping_timestamps_[id] << " / packet id = " << id;
}

void NetworkWorker::SendPendingEvents() {
    // we know the event won't be deleted until we leave this method
    // so using a pointer (instead of a shared_ptr) is fine
    QVector<Event*> to_send;
    QMutexLocker lock(&pending_events_mutex_);
    auto it = pending_.begin();
    int i = 0;
    while(it != pending_.end()) {
      while(i < 6 && it != pending_.end()) {
        // each packet contains at most 5 events in order not ot have the datagram splitted by the underlying network layers
        // TODO: add events until the datagram is 512 bytes (more robust)
        to_send.push_back(it->second.get());
        VLOG(9) << "Preparing to send the event with id " << it->second->GetId();
        i++;
        ++it;
      }
      QByteArray buffer;
      QDataStream stream(&buffer, QIODevice::OpenModeFlag::WriteOnly);
      quint32 packet_id = PrepareHeader(stream, kEventPacketId);
      stream << (quint8) to_send.size();
      for(Event* evt : to_send) {
        stream << *evt;
      }
      assert(stream.status() == QDataStream::Status::Ok);
      socket_.write(buffer);
      to_send.clear();
      i = 0;
      VLOG(9) << "Packet event with id " << packet_id << " sent";
    }
    VLOG(9) << "All pending events sent";
}

void NetworkWorker::AddEvent(std::unique_ptr<Event> event) {
  quint64 id = GetNextEventId();
  event->SetId(id);
  QMutexLocker lock(&pending_events_mutex_);
  pending_[id] = std::move(event);
}

quint32 NetworkWorker::PrepareHeader(QDataStream& stream, quint8 packet_type) {
  assert(stream.status() == QDataStream::Ok);
  quint32 packet_id = GetNextPacketId();
  stream << kProtocolId << kClientVersion << client_id_ << packet_id << packet_type;
  return packet_id;
}

void NetworkWorker::CleanPingData() {
  quint32 now = game_timer_->GetTimestamp();
  auto it = ping_timestamps_.begin();
  while(it != ping_timestamps_.end()) {
    if(it->second + 5000 < now) {
      it = ping_timestamps_.erase(it);
    } else {
      ++it;
    }
  }
}

bool NetworkWorker::CheckStreamStatus(const QDataStream& stream) const {
  if(stream.status() != QDataStream::Ok) {
    LOG(WARNING) << "Deserialization stream status is not OK (code is: " << (int) stream.status() << "), the current message will be lost";
    return false;
  }
  return true;
}



}
