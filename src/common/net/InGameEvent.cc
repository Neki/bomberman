#include "InGameEvent.h"

namespace common {
namespace net {

InGameEvent::InGameEvent(quint8 character_id, quint32 id, quint32 timestamp)
  : Event(id, timestamp),
    character_id_(character_id) {
}

InGameEvent::InGameEvent(quint8 character_id, quint64 timestamp)
  : Event(timestamp),
    character_id_(character_id) {
}

InGameEvent::~InGameEvent() {}

quint8 InGameEvent::GetCharacterId() const {
  return character_id_;
}

void InGameEvent::SerializeBaseInGameEvent(QDataStream& stream, EventId event_id) const {
  Event::SerializeBaseEvent(stream, event_id);
  stream << character_id_;
}

bool InGameEvent::operator==(const InGameEvent& other) const {
  return Event::operator==(other) && other.character_id_ == character_id_;
}

}
}
