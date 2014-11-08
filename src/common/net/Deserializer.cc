#include "Deserializer.h"

namespace common {
namespace net {

EventId Deserializer::GetNextEventId(QDataStream &stream) {
  quint8 id;
  stream >> id;
  switch(id) {
    case EventId::kBombEventId:
      return EventId::kBombEventId;
    case EventId::kMoveEventId:
      return EventId::kMoveEventId;
    case EventId::kPlayerLeftEvent:
      return EventId::kPlayerLeftEvent;
    default:
      // TODO(faucon_b) gracefull error handling
      return EventId::kUnknownEventId;
  }
}

std::unique_ptr<InGameEvent> Deserializer::DeserializeInGameEvent(QDataStream& stream) {
  EventId event_type = GetNextEventId(stream);
  switch(event_type) {
    case kBombEventId:
      return std::unique_ptr<InGameEvent>(new BombEvent(DeserializeBombEvent(stream)));
    case kMoveEventId:
      return std::unique_ptr<InGameEvent>(new MoveEvent(DeserializeMoveEvent(stream)));
    case kPlayerLeftEvent:
      return std::unique_ptr<InGameEvent>(new PlayerLeftEvent(DeserializePlayerLeftEvent(stream)));
    case kUnknownEventId:
    default:
      // TODO error handling
      return std::unique_ptr<InGameEvent>();
      break;
  }
}

BaseEventData Deserializer::DeserializeBaseInGameEvent(QDataStream& stream) {
  BaseEventData data;
  stream >> data.id;
  stream >> data.timestamp;
  stream >> data.character_id;
  return data;
}

BombEvent Deserializer::DeserializeBombEvent(QDataStream& stream) {
  BaseEventData data = DeserializeBaseInGameEvent(stream);
  QPoint position;
  stream >> position;
  return BombEvent(position, data.character_id, data.id, data.timestamp);
}

MoveEvent Deserializer::DeserializeMoveEvent(QDataStream& stream) {
  BaseEventData data = DeserializeBaseInGameEvent(stream);
  QPoint position;
  QPoint destination;
  Direction direction;
  stream >> position;
  stream >> destination;
  quint8 direction_int;
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
  return MoveEvent(position, destination, direction, data.character_id, data.id, data.timestamp);
}

PlayerLeftEvent Deserializer::DeserializePlayerLeftEvent(QDataStream& stream) {
  BaseEventData data = DeserializeBaseInGameEvent(stream);
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
  return PlayerLeftEvent(reason, data.character_id, data.id, data.timestamp);
}

EntityId Deserializer::GetNextEntityId(QDataStream& stream) {
  quint8 type;
  stream >> type;
  switch(type) {
    case EntityId::kWallId:
      return kWallId;
    case EntityId::kBombId:
      return kBombId;
    case EntityId::kBonusId:
      return kBonusId;
    case EntityId::kBlockId:
      return kBlockId;
    case EntityId::kFireId:
      return kFireId;
    case EntityId::kCharacterId:
      return kCharacterId;
    case EntityId::kUnknownEntity: /* fall-through */
    default: // TODO error
     return kUnknownEntity;
 }
}

std::unique_ptr<Entity> Deserializer::DeserializeEntity(QDataStream& stream) {
  EntityId type = GetNextEntityId(stream);
  switch(type) {
    case EntityId::kWallId:
      return std::unique_ptr<Entity>(new Wall(DeserializeWall(stream)));
    case EntityId::kBombId:
      return std::unique_ptr<Entity>(new Bomb(DeserializeBomb(stream)));
    case EntityId::kBonusId:
      return std::unique_ptr<Entity>(new Bonus(DeserializeBonus(stream)));
    case EntityId::kBlockId:
      return std::unique_ptr<Entity>(new Block(DeserializeBlock(stream)));
    case EntityId::kFireId:
      return std::unique_ptr<Entity>(new Fire(DeserializeFire(stream)));
    case EntityId::kCharacterId:
      return std::unique_ptr<Entity>(new Character(DeserializeCharacter(stream)));
    case EntityId::kUnknownEntity: /* fall-through */
    default:
      return std::unique_ptr<Entity>();
  }
}

BaseEntityData Deserializer::DeserializeBaseEntity(QDataStream& stream) {
  BaseEntityData data;
  stream >> data.id;
  stream >> data.temp_id;
  stream >> data.position;
  return data;
}

Block Deserializer::DeserializeBlock(QDataStream& stream) {
  BaseEntityData data = DeserializeBaseEntity(stream);
  return Block(data.position);
}

Fire Deserializer::DeserializeFire(QDataStream& stream) {
  BaseEntityData data = DeserializeBaseEntity(stream);
  quint32 set_time;
  stream >> set_time;
  return Fire(data.position, set_time);
}

Wall Deserializer::DeserializeWall(QDataStream& stream) {
  BaseEntityData data = DeserializeBaseEntity(stream);
  return Wall(data.position);
}

Character Deserializer::DeserializeCharacter(QDataStream& stream) {
  BaseEntityData data = DeserializeBaseEntity(stream);
  quint32 power;
  float speed;
  quint32 number_of_bombs;
  stream >> power;
  stream >> speed;
  stream >> number_of_bombs;
  return Character(data.position, power, speed, number_of_bombs);
}

Bonus Deserializer::DeserializeBonus(QDataStream& stream) {
  BaseEntityData data = DeserializeBaseEntity(stream);
  return Bonus(data.position);
}

Bomb Deserializer::DeserializeBomb(QDataStream& stream) {
  BaseEntityData data = DeserializeBaseEntity(stream);
  quint32 set_time;
  quint32 explosion_time;
  quint8 power;
  stream >> set_time;
  stream >> explosion_time;
  stream >> power;
  return Bomb(data.position, set_time, explosion_time, power);
}

}
}
