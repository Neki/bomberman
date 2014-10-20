#include "GameNetworkWorker.h"
#include "easylogging++.h"
#include "src/common/net/EventId.h"
#include "src/common/net/Deserializer.h"

namespace net {

GameNetworkWorker::GameNetworkWorker(quint16 port, std::shared_ptr<GameTimer> game_timer, std::vector<Client> clients)
  : port_(port),
    game_timer_(game_timer),
    last_packet_id_(0) {
  socket_.bind(QHostAddress::LocalHost, port_);
  for(Client client : clients) {
    clients_.insert(std::pair<int, Client>(client.GetId(), client));
  }
}

void GameNetworkWorker::ReadPendingDatagrams() {
  while(socket_.hasPendingDatagrams()) {
    QByteArray datagram;
    datagram.resize(socket_.pendingDatagramSize());
    QHostAddress sender;
    quint16 sender_port;
    socket_.readDatagram(datagram.data(), datagram.size(), &sender, &sender_port);
    ProcessDatagram(datagram);
  }
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
    EventId event_type = Deserializer::GetNextEventId(stream);
    switch(event_type) {
      case EventId::kBombEventId: {
        BombEvent event = Deserializer::DeserializeBombEvent(stream);
        auto c_event = ClientEvent<BombEvent>(event, client, game_timer_->GetTimestamp());
        break;
      }
      case EventId::kUnknownEventId: /* fall-through */
      default:
        LOG(WARNING) << "Received unknown event type: " << event_type << ", dropping the datagram.";
        return;
    }
  }

}

void GameNetworkWorker::SendPongPacket(const Client& client, quint32 packet_id) {
  QByteArray buffer;
  QDataStream stream(&buffer, QIODevice::OpenModeFlag::WriteOnly);
  PrepareHeader(stream, kPingPacketId);
  stream << packet_id;
  stream << game_timer_->GetTimestamp();
  socket_.writeDatagram(buffer, client.GetAddress(), client.GetPort());
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

}
