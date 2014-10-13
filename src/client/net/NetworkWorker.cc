#include "NetworkWorker.h"
#include <QVector>
#include <QTime>
#include <QMutexLocker>


namespace common {
namespace net {

NetworkWorker::NetworkWorker(quint8 client_id, QHostAddress address, quint16 server_port, quint16 local_port)
  : buffer_stream_(&buffer_, QIODevice::OpenModeFlag::WriteOnly),
    client_id_(client_id),
    time_between_packets_(50),
    timer_(this) {
  socket_.connectToHost(address, server_port);
  socket_.bind(QHostAddress::LocalHost, local_port);
  connect(&timer_, SIGNAL(timeout()), this, SLOT(SendPendingEvents()));
  connect(&socket_, SIGNAL(readyRead()), this, SLOT(ReadPendingDatagrams()));
  timer_.start(100);
}

quint64 NetworkWorker::GetNextEventId() {
  last_event_id_ += 1;
  return last_event_id_;
}

quint64 NetworkWorker::GetNextPacketId() {
  last_packet_id_ += 1;
  return last_packet_id_;
}

void NetworkWorker::ReadPendingDatagrams() {
  while(socket_.hasPendingDatagrams()) {
    QByteArray datagram;
    datagram.resize(socket_.pendingDatagramSize());
    QHostAddress sender;
    quint16 sender_port;
    socket_.readDatagram(datagram.data(), datagram.size(), &sender, &sender_port);
    ProcessDatagram(datagram);
  }

}

void NetworkWorker::ProcessDatagram(const QByteArray& datagram) {
  // Silently drop the datagram for now
   (void) datagram;
}

void NetworkWorker::SendPendingEvents() {
    buffer_.clear();
    // we know the event won't be deleted until we leave this method
    // so using a pointer (instead of a shared_ptr) is fine
    QVector<Event*> to_send;
    QMutexLocker lock(&pending_events_mutex_);
    for(const auto& it : pending_) {
      to_send.push_back(it.second.get());
      // TODO: make sure we don't send too many events (512 bytes max)
    }
    lock.unlock();
    PrepareHeader(buffer_stream_, kEventPacketId);
    buffer_stream_ << to_send;
    socket_.write(buffer_);
}

void NetworkWorker::AddEvent(std::unique_ptr<Event> event) {
  quint64 id = GetNextEventId();
  event->SetId(id);
  QMutexLocker lock(&pending_events_mutex_);
  pending_[id] = std::move(event);
}

quint64 NetworkWorker::PrepareHeader(QDataStream& stream, quint8 packet_type) {
  quint64 packet_id = GetNextPacketId();
  stream << kProtocolId << kClientVersion << client_id_ << packet_id << packet_type;
  return packet_id;
}

}
}
