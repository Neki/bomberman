#include "GameNetworkWorker.h"
#include "easylogging++.h"
#include "src/common/net/EventId.h"
#include "src/common/net/Deserializer.h"

namespace net {

GameNetworkWorker::GameNetworkWorker(quint16 port, std::shared_ptr<GameTimer> game_timer, std::vector<Client> clients)
  : port_(port),
    game_timer_(game_timer),
    last_packet_id_(1),
    last_event_id_(1) {
  QObject::connect(&socket_, SIGNAL(readyRead()), this, SLOT(ReadPendingDatagrams()));
  QObject::connect(&socket_, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(SocketError(QAbstractSocket::SocketError)));
  socket_.bind( port_);
  for(Client client : clients) {
    clients_.insert(std::pair<int, Client>(client.GetId(), client));
  }
  LOG(DEBUG) << "In game network worker initialized and ready on port " << port_;
}

void GameNetworkWorker::ReadPendingDatagrams() {
  VLOG(9) << "Reading pending datagrams...";
  while(socket_.hasPendingDatagrams()) {
    QByteArray datagram;
    datagram.resize(socket_.pendingDatagramSize());
    QHostAddress sender;
    quint16 sender_port;
    socket_.readDatagram(datagram.data(), datagram.size(), &sender, &sender_port);
    ProcessDatagram(datagram);
  }
}

void GameNetworkWorker::SocketError(QAbstractSocket::SocketError error) {
  LOG(ERROR) << "Error on socket: " << socket_.errorString().toStdWString();
  (void) error;
}


void GameNetworkWorker::ProcessDatagram(const QByteArray& datagram) {
  QDataStream stream(datagram);
  if(!CheckProtocolAndVersion(stream)) {
    LOG(WARNING) << "Protocol or version ID mismatch, dropping datagram.";
    return;
  }
  quint8 client_id = GetClientId(stream);
  VLOG(5) << "Datagram comes from client " << client_id;
  auto it = clients_.find(client_id);
  if(it == clients_.end()) {
    LOG(WARNING) << "Got a datagram with client id " << client_id << " that does not match a registered client, dropping it.";
    return;
  }
  Client client = it->second;
  quint32 packet_id = GetPacketId(stream);
  VLOG(5) << "Received datagram packet id: " << packet_id;
  quint8 packet_type = GetPacketType(stream);
  switch(packet_type) {
    case kPingPacketId:
      VLOG(5) << "The datagram is a ping packet.";
      ProcessPingPacket(stream, client, packet_id);
      break;
    case kEventPacketId:
      VLOG(5) << "The datagram is an event packet.";
      ProcessEventPacket(stream, client, packet_id);
      break;
    default:
      LOG(WARNING) << "Received unknown packet type " << packet_type << ", dropping datagram.";
      break;
  }
}

bool GameNetworkWorker::CheckProtocolAndVersion(QDataStream &stream) {
  quint8 protocol_id;
  quint8 server_version;
  stream >> protocol_id;
  stream >> server_version;
  quint8 accepted_version = GameNetworkWorker::kServerVersion;
  quint8 accepted_protocol_id = GameNetworkWorker::kProtocolId;
  if(protocol_id != accepted_protocol_id) {
    LOG(WARNING) << "Received unexpected protocol ID: got " << protocol_id << ", expected " << accepted_protocol_id;
    return false;
  }
  if(server_version != accepted_version) {
    LOG(WARNING) << "Received unsupported server version: got " << server_version << ", but only version " << accepted_version << " is supported by this client";
    return false;
  }
  return true;
}

quint8 GameNetworkWorker::GetPacketType(QDataStream& stream) {
  quint8 packet_id;
  stream >> packet_id;
  return packet_id;
}

quint32 GameNetworkWorker::GetPacketId(QDataStream& stream) {
  quint32 packet_id;
  stream >> packet_id;
  return packet_id;
}

quint8 GameNetworkWorker::GetClientId(QDataStream& stream) {
  quint8 client_id;
  stream >> client_id;
  return client_id;
}

void GameNetworkWorker::ProcessPingPacket(QDataStream& stream, const Client& client, quint32 packet_id) {
  (void) stream; // unused for now, the ping content does not matter
  SendPongPacket(client, packet_id);
}

void GameNetworkWorker::ProcessEventPacket(QDataStream& stream, const Client& client, quint32 packet_id) {
  (void) packet_id;
  quint8 events_size;
  stream >> events_size;
  for(int i = 0; i < events_size; i++) {
    std::unique_ptr<InGameEvent> event = Deserializer::DeserializeInGameEvent(stream);
    if(event.get() == nullptr) {
      LOG(WARNING) << "Could not deserialize the received event. Dropping it.";
      return;
    }
    VLOG(9) << "Deserialized event has ID " << event->GetId();
    if(event->GetId() < last_event_id_) {
      VLOG(8) << "The client has sent an event that has already been processed (according to its ID).";
      return;
    }
    auto client_event = std::unique_ptr<BaseClientEvent>(new BaseClientEvent(std::move(event), client, game_timer_->GetTimestamp()));
    HandlePendingEvent(std::move(client_event));
  }
}

// TODO: defends against a client attacking the server by sending bad events id
void GameNetworkWorker::HandlePendingEvent(std::unique_ptr<BaseClientEvent> event) {
  event_cache_.insert(std::pair<quint32, std::unique_ptr<BaseClientEvent>>(event->GetEvent()->GetId(), std::move(event)));
  EmitReadyEvents();
}

void GameNetworkWorker::EmitReadyEvents() {
  auto it = event_cache_.begin();
  while(it != event_cache_.end()) {
    it = event_cache_.find(last_event_id_);
    if(it != event_cache_.end()) {
      EmitterVisitor visitor(this, it->second.get());
      it->second->GetEvent()->Accept(visitor);
      event_cache_.erase(it->first);
      last_event_id_++;
    }
  }
}

void GameNetworkWorker::SendPongPacket(const Client& client, quint32 packet_id) {
  QByteArray buffer;
  QDataStream stream(&buffer, QIODevice::OpenModeFlag::WriteOnly);
  PrepareHeader(stream, kPingPacketId);
  stream << packet_id;
  quint32 timestamp = game_timer_->GetTimestamp();
  stream << timestamp;
  socket_.writeDatagram(buffer, client.GetAddress(), client.GetPort());
  VLOG(9) << "Answered pong with timestamp " << timestamp << " to the ping with id " << packet_id;
  VLOG(9) << "Client was at address " << client.GetAddress().toString().toStdWString() << ":" << client.GetPort();
}

void GameNetworkWorker::PrepareHeader(QDataStream& stream, quint8 packet_type) {
  stream << kProtocolId;
  stream << kServerVersion;
  stream << GetNextPacketId();
  stream << packet_type;
}

quint32 GameNetworkWorker::GetNextPacketId() {
  last_packet_id_ += 1;
  return last_packet_id_;
}

void GameNetworkWorker::EmitEvent(ClientEvent<BombEvent> event) {
  VLOG(EVENT_READY_LOG_LEVEL) << "Network worker: bomb event ready / id: " << event.getEventData().GetId();
  emit BombEventReceived(event);
}

void GameNetworkWorker::EmitEvent(ClientEvent<MoveEvent> event) {
  VLOG(EVENT_READY_LOG_LEVEL) << "Network worker: move event ready / id: " << event.getEventData().GetId();
  emit MoveEventReceived(event);
}

void GameNetworkWorker::EmitEvent(ClientEvent<PlayerLeftEvent> event) {
  VLOG(EVENT_READY_LOG_LEVEL) << "Network worker: player left event ready / id: " << event.getEventData().GetId();
  emit PlayerLeftEventReceived(event);
}

}
