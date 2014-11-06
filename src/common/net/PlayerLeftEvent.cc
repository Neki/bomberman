#include "PlayerLeftEvent.h"
#include "EventId.h"

namespace common {
namespace net {

PlayerLeftEvent::PlayerLeftEvent(QuitReason reason, quint8 character_id, quint32 id, quint32 timestamp)
  : InGameEvent(character_id, id, timestamp),
    reason_(reason) {}


PlayerLeftEvent::PlayerLeftEvent(QuitReason reason, quint8 character_id, quint32 timestamp)
  : InGameEvent(character_id, timestamp),
    reason_(reason) {}

QuitReason PlayerLeftEvent::GetReason() const {
  return reason_;
}

void PlayerLeftEvent::Serialize(QDataStream& stream) const {
  SerializeBaseInGameEvent(stream, EventId::kPlayerLeftEvent);
  stream << GetReason();
}

void PlayerLeftEvent::Accept(GameEventVisitor& visitor) {
  visitor.Visit(*this);
}

bool PlayerLeftEvent::operator==(const PlayerLeftEvent& event) const {
  return InGameEvent::operator==(event) && reason_ == event.reason_;
}
}
}
