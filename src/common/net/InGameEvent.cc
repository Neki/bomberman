#include "InGameEvent.h"

namespace common {
namespace net {

InGameEvent::InGameEvent(quint8 character_id, quint32 id, quint32 timestamp)
  : id_(id),
    timestamp_(timestamp),
    character_id_(character_id) {
}

InGameEvent::InGameEvent(quint8 character_id, quint64 timestamp) :
  InGameEvent(character_id, 0, timestamp) {}

InGameEvent::~InGameEvent() {}

quint8 InGameEvent::GetCharacterId() const {
  return character_id_;
}

quint32 InGameEvent::GetId() const {
  return id_;
}

void InGameEvent::SetId(quint32 id) {
  id_ = id;
}

quint32 InGameEvent::GetTimestamp() const {
  return timestamp_;
}

void InGameEvent::SerializeBaseInGameEvent(QDataStream& stream, EventId event_id) const {
  stream << (quint8) event_id;
  stream << GetId();
  stream << GetTimestamp();
  stream << character_id_;
}

bool InGameEvent::operator==(const InGameEvent& other) const {
  return id_ == other.id_ && timestamp_ == other.timestamp_ && other.character_id_ == character_id_;
}

QDataStream& operator<<(QDataStream& stream, const InGameEvent& event) {
  event.Serialize(stream);
  return stream;
}

}
}
