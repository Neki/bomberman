#include "GameNetworkWorker.h"
#include "easylogging++.h"
#include "src/common/net/EventId.h"
#include "src/common/net/Deserializer.h"
#include <cassert>

namespace net {

GameNetworkWorker::GameNetworkWorker(quint16 port, std::shared_ptr<GameTimer> game_timer, std::weak_ptr<World> world, std::vector<Client> clients)
  : port_(port),
    game_timer_(game_timer),
    last_packet_id_(1),
    world_ptr_(world),
    send_entities_timer_(),
    detect_disconnect_timer_() {
  QObject::connect(&socket_, SIGNAL(readyRead()), this, SLOT(ReadPendingDatagrams()));
  QObject::connect(&socket_, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(SocketError(QAbstractSocket::SocketError)));
  socket_.bind( port_);
  for(Client client : clients) {
    clients_.insert(std::pair<int, Client>(client.GetId(), client));
    last_event_ids_[client.GetId()] = 0; // not event has been ACKed yet for this client (the first event ID will be 1)
    last_received_pings_[client.GetId()] = game_timer_->GetTimestamp();
  }
  QObject::connect(&send_entities_timer_, &QTimer::timeout, this, &GameNetworkWorker::BroadcastWorld);
  send_entities_timer_.start(100);
  QObject::connect(&detect_disconnect_timer_, &QTimer::timeout, this, &GameNetworkWorker::DetectConnectionLost);
  detect_disconnect_timer_.start(kDisconnectTimeout / 3);
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
  if(!CheckStreamStatus(stream)) {
    LOG(WARNING) << "Could not deserialize the client id.";
    return;
  }
  auto it = clients_.find(client_id);
  if(it == clients_.end()) {
    LOG(WARNING) << "Got a datagram with client id " << (int) client_id << " that does not match a registered client, dropping it.";
    return;
  }
  Client client = it->second;
  if(!client.IsConnected()) {
    LOG(WARNING) << "Received a datagram from a previously disconnected client. This server does not support client reconnection ; dropping the datagram";
  }
  VLOG(5) << "Datagram comes from client " << client.GetId();
  quint32 packet_id = GetPacketId(stream);
  if(!CheckStreamStatus(stream)) {
    LOG(WARNING) << "Could not deserialize the packet id.";
    return;
  }
  VLOG(5) << "Received datagram packet id: " << packet_id;
  quint8 packet_type = GetPacketType(stream);
  if(!CheckStreamStatus(stream)) {
    LOG(WARNING) << "Could not deserialize the packet type.";
    return;
  }
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
  assert(stream.status() == QDataStream::Ok);
  quint8 protocol_id;
  quint8 server_version;
  stream >> protocol_id;
  stream >> server_version;

  if(!CheckStreamStatus(stream)) {
    LOG(WARNING) << "Could not deserialize the protocol and version.";
    return false;
  }

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
  assert(stream.status() == QDataStream::Ok);
  quint8 packet_id;
  stream >> packet_id;
  return packet_id;
}

quint32 GameNetworkWorker::GetPacketId(QDataStream& stream) {
  assert(stream.status() == QDataStream::Ok);
  quint32 packet_id;
  stream >> packet_id;
  return packet_id;
}

quint8 GameNetworkWorker::GetClientId(QDataStream& stream) {
  assert(stream.status() == QDataStream::Ok);
  quint8 client_id;
  stream >> client_id;
  return client_id;
}

void GameNetworkWorker::ProcessPingPacket(QDataStream& stream, const Client& client, quint32 packet_id) {
  (void) stream; // unused for now, the ping content does not matter
  last_received_pings_[client.GetId()] = game_timer_->GetTimestamp();
  SendPongPacket(client, packet_id);
}

void GameNetworkWorker::ProcessEventPacket(QDataStream& stream, const Client& client, quint32 packet_id) {
  assert(stream.status() == QDataStream::Ok);
  (void) packet_id;
  quint8 events_size;
  stream >> events_size;

  if(!CheckStreamStatus(stream)) {
    LOG(WARNING) << "Could not deserialize the number of events.";
    return;
  }

  for(int i = 0; i < events_size; i++) {
    std::unique_ptr<InGameEvent> event = Deserializer::DeserializeInGameEvent(stream);
    if(stream.status() != QDataStream::Ok) {
      LOG(WARNING) << "Stream is in an invalid state after having deserialized the event. Continuing anyway.";
    }
    if(event.get() == nullptr) {
      LOG(WARNING) << "Could not deserialize the received event. Dropping remaining data.";
      return;
    }
    VLOG(9) << "Deserialized event has ID " << event->GetId();
    if(event->GetId() <= last_event_ids_[client.GetId()]) {
      VLOG(8) << "The client has sent an event that has already been processed (according to its ID).";
      continue;
    }
    auto client_event = std::unique_ptr<BaseClientEvent>(new BaseClientEvent(std::move(event), client, game_timer_->GetTimestamp()));
    HandlePendingEvent(std::move(client_event));
  }
  EmitReadyEvents(client);
}

// TODO: defends against a client attacking the server by sending bad events id
void GameNetworkWorker::HandlePendingEvent(std::unique_ptr<BaseClientEvent> event) {
  Client client = event->GetClient();
  auto pair = std::pair<const quint32, std::unique_ptr<BaseClientEvent>>(event->GetEvent()->GetId(), std::move(event));
  event_cache_[client.GetId()].insert(std::move(pair));
}

void GameNetworkWorker::EmitReadyEvents(Client client) {
  quint8 client_id = client.GetId();
  // look if the next event from this client (ordered by id) has been received
  auto it = event_cache_[client_id].find(last_event_ids_[client_id] + 1);
  bool send_ack = false;
  while(it != event_cache_[client_id].end()) {
    // if yes, send it to the application
    EmitterVisitor visitor(this, it->second.get());
    it->second->GetEvent()->Accept(visitor);
    event_cache_[client_id].erase(it);
    // this event will be ACKed
    last_event_ids_[client_id]++;
    send_ack = true;
    // update iterator
    it = event_cache_[client_id].find(last_event_ids_[client_id] + 1);
  }
  if(send_ack) {
    SendAckPacket(client, last_event_ids_[client_id]);
  }
}

void GameNetworkWorker::SendAckPacket(const Client& client, quint32 event_id) {
  QByteArray buffer;
  QDataStream stream(&buffer, QIODevice::OpenModeFlag::WriteOnly);
  PrepareHeader(stream, kEventAckPacketId);
  stream << event_id;
  assert(stream.status() == QDataStream::Ok);
  socket_.writeDatagram(buffer, client.GetAddress(), client.GetPort());
  VLOG(9) << "Sent ACK packet for ids <= " << (int) event_id << " to client ID " << (int) client.GetId();
}

void GameNetworkWorker::SendPongPacket(const Client& client, quint32 packet_id) {
  QByteArray buffer;
  QDataStream stream(&buffer, QIODevice::OpenModeFlag::WriteOnly);
  PrepareHeader(stream, kPingPacketId);
  stream << packet_id;
  quint32 timestamp = game_timer_->GetTimestamp();
  stream << timestamp;
  assert(stream.status() == QDataStream::Ok);
  socket_.writeDatagram(buffer, client.GetAddress(), client.GetPort());
  VLOG(9) << "Answered pong with timestamp " << timestamp << " to the ping with id " << packet_id;
  VLOG(9) << "Client was at address " << client.GetAddress().toString().toStdWString() << ":" << client.GetPort();
}

quint32 GameNetworkWorker::PrepareHeader(QDataStream& stream, quint8 packet_type) {
  assert(stream.status() == QDataStream::Ok);
  quint32 packet_id = GetNextPacketId();
  stream << kProtocolId;
  stream << kServerVersion;
  stream << packet_id;
  stream << packet_type;
  return packet_id;
}

quint32 GameNetworkWorker::GetNextPacketId() {
  last_packet_id_ += 1;
  return last_packet_id_;
}

void GameNetworkWorker::EmitEvent(ClientEvent<BombEvent> event) {
  VLOG(EVENT_READY_LOG_LEVEL) << "Network worker: bomb event ready / client id: " << (int) event.GetClientId() << " / id: " << event.GetEventData().GetId();
  emit BombEventReceived(event);
}

void GameNetworkWorker::EmitEvent(ClientEvent<MoveEvent> event) {
  VLOG(EVENT_READY_LOG_LEVEL) << "Network worker: move event ready / client id: " << (int) event.GetClientId() << " / id: " << event.GetEventData().GetId();
  emit MoveEventReceived(event);
}

void GameNetworkWorker::EmitEvent(ClientEvent<PlayerLeftEvent> event) {
  VLOG(EVENT_READY_LOG_LEVEL) << "Network worker: player left event ready / client id: " << (int) event.GetClientId() << " / id: " << event.GetEventData().GetId();
  emit PlayerLeftEventReceived(event);
}

void GameNetworkWorker::BroadcastWorld() {
  quint32 timestamp = game_timer_->GetTimestamp();
  VLOG(9) << "Broadcasting the world state to clients, timestamp is " << timestamp;
  auto world = world_ptr_.lock();
  if(world.get() == nullptr) {
    LOG(WARNING) << "The World has gone out of scope, can not send it to clients!";
    return;
  }
  std::vector<Entity*> to_send;
  // do not put to many entites in the same packet to prevent the packet from
  // being cut by the network layer
  for(int i = 0; i < world->GetWidth(); i++)  {
    for(int j = 0; j < world->GetHeight(); j++) {
      QPoint point(i, j);// TODO check indices
      for(auto it = world->IteratorAtBegin(point); it != world->IteratorAtEnd(point); ++it) {
        to_send.push_back(it->get());
      }
    }
  }
  for(auto it = world->CharacterIteratorBegin(); it != world->CharacterIteratorEnd(); ++it) {
    to_send.push_back(it->get());
  }
  auto it = to_send.begin();
  while(it != to_send.end()) {
    QByteArray buffer;
    QDataStream stream(&buffer, QIODevice::OpenModeFlag::WriteOnly);
    quint32 packet_id = PrepareHeader(stream, kEntitiesPacketId);
    stream << timestamp;
    std::vector<Entity*> packet;
    for(int i = 0; i < 10 && it != to_send.end(); ++i) {
      packet.push_back(*it);
      ++it;
    }
    stream << (quint8) packet.size();
    for(Entity* entity: packet) {
      stream << *entity;
    }
    for(auto p: clients_) {
      socket_.writeDatagram(buffer, buffer.size(), p.second.GetAddress(), p.second.GetPort());
    }
    VLOG(9) << "Sent the entities packet with ID: " << packet_id << " to all the clients";
  }
}

void GameNetworkWorker::DetectConnectionLost() {
  for(auto it = last_received_pings_.begin(); it != last_received_pings_.end(); ++it) {
    if(game_timer_->GetTimestamp() > it->second + kDisconnectTimeout) {
      auto itt = clients_.find(it->first);
      assert(itt != clients_.end());
      Client client = itt->second;
      client.SetConnected(false);
      LOG(INFO) << "The client " << (int) client.GetId() << " did not send a ping for at least " << (int) kDisconnectTimeout << " seconds ; marking it as disconnected.";
      emit ConnectionLost(client);
      last_received_pings_.erase(it);
    }
  }
}

bool GameNetworkWorker::CheckStreamStatus(const QDataStream& stream) const {
  if(stream.status() != QDataStream::Ok) {
    LOG(WARNING) << "Deserialization stream status is not OK (code is: " << (int) stream.status() << "), the current message will be lost.";
    return false;
  }
  return true;
}


}
