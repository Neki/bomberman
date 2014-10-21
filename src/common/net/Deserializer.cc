#include "Deserializer.h"

namespace common {
namespace net {

EventId Deserializer::GetNextEventId(QDataStream &stream) {
  quint32 id;
  stream >> id;
  switch(id) {
    case EventId::kBombEventId:
      return EventId::kBombEventId;
    case EventId::kMoveEventId:
      return EventId::kMoveEventId;
    case EventId::kPlayerJoinedEvent:
      return EventId::kPlayerJoinedEvent;
    case EventId::kPlayerLeftEvent:
      return EventId::kPlayerLeftEvent;
    case EventId::kSetAdminEvent:
      return EventId::kSetAdminEvent;
    case EventId::kSettingsEvent:
      return EventId::kSettingsEvent;
    default:
      // TODO(faucon_b) gracefull error handling
      return EventId::kUnknownEventId;
  }
}

std::unique_ptr<Event> Deserializer::DeserializeEvent(QDataStream& stream) {
  EventId event_type = GetNextEventId(stream);
  switch(event_type) {
    case kBombEventId:
      return std::unique_ptr<Event>(new BombEvent(DeserializeBombEvent(stream)));
    case kMoveEventId:
      return std::unique_ptr<Event>(new MoveEvent(DeserializeMoveEvent(stream)));
    case kPlayerLeftEvent:
      return std::unique_ptr<Event>(new PlayerLeftEvent(DeserializePlayerLeftEvent(stream)));
    case kPlayerJoinedEvent:
      return std::unique_ptr<Event>(new PlayerJoinedEvent(DeserializePlayerJoinedEvent(stream)));
    case kSettingsEvent:
      return std::unique_ptr<Event>(new SettingsEvent(DeserializeSettingsEvent(stream)));
    case kSetAdminEvent:
      return std::unique_ptr<Event>(new SetAdminEvent(DeserializeSetAdminEvent(stream)));
    case kUnknownEventId:
    default:
      // TODO error handling
      return std::unique_ptr<Event>();
      break;
  }
}

BaseEventData Deserializer::DeserializeBaseEvent(QDataStream& stream) {
  BaseEventData data;
  stream >> data.client_version;
  stream >> data.id;
  stream >> data.timestamp;
  return data;
}

BombEvent Deserializer::DeserializeBombEvent(QDataStream& stream) {
  BaseEventData data = DeserializeBaseEvent(stream);
  QPoint position;
  stream >> position;
  return BombEvent(position, data.id, data.timestamp);
}

MoveEvent Deserializer::DeserializeMoveEvent(QDataStream& stream) {
  BaseEventData data = DeserializeBaseEvent(stream);
  QPoint position;
  Direction direction;
  stream >> position;
  int direction_int;
  stream >> direction_int;
  switch(direction_int) {
    case Direction::UP:
      direction = Direction::UP;
      break;
    case Direction::DOWN:
      direction = Direction::DOWN;
      break;
    case Direction::LEFT:
      direction = Direction::LEFT;
      break;
    case Direction::RIGHT:
      direction = Direction::RIGHT;
      break;
    default:
      direction = Direction::UP;
      // TODO ERROR
       break;
  }
  return MoveEvent(position, direction, data.id, data.timestamp);
}

PlayerJoinedEvent Deserializer::DeserializePlayerJoinedEvent(QDataStream& stream) {
  BaseEventData data = DeserializeBaseEvent(stream);
  QString player_name;
  stream >> player_name;
  return PlayerJoinedEvent(player_name, data.id, data.timestamp);
}

PlayerLeftEvent Deserializer::DeserializePlayerLeftEvent(QDataStream& stream) {
  BaseEventData data = DeserializeBaseEvent(stream);
  int reason_int;
  QuitReason reason;
  stream >> reason_int;
  switch(reason_int) {
    case QuitReason::TIMEOUT: // TODO(faucon_b) : this probably should be an error
      reason = QuitReason::TIMEOUT;
      break;
    case QuitReason::LEFT_GAME:
      reason = QuitReason::LEFT_GAME;
      break;
    default: // TODO error
      reason = QuitReason::TIMEOUT;
      break;
  }
  return PlayerLeftEvent(reason, data.id, data.timestamp);
}

SetAdminEvent Deserializer::DeserializeSetAdminEvent(QDataStream& stream) {
  BaseEventData data = DeserializeBaseEvent(stream);
  return SetAdminEvent(data.id, data.timestamp);
}

SettingsEvent Deserializer::DeserializeSettingsEvent(QDataStream& stream) {
  BaseEventData data = DeserializeBaseEvent(stream);
  return SettingsEvent(data.id, data.timestamp);
}

}
}
