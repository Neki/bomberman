#include "PlayerLeftEvent.h"
#include "EventId.h"

namespace common {
namespace net {

PlayerLeftEvent::PlayerLeftEvent(QuitReason reason, quint32 id, quint32 timestamp)
  : InGameEvent(id, timestamp),
    reason_(reason) {}


PlayerLeftEvent::PlayerLeftEvent(QuitReason reason, quint32 timestamp)
  : InGameEvent(timestamp),
    reason_(reason) {}

QuitReason PlayerLeftEvent::GetReason() const {
  return reason_;
}

void PlayerLeftEvent::Serialize(QDataStream& stream) const {
  SerializeBaseEvent(stream, EventId::kPlayerLeftEvent);
  stream << GetReason();
}

void PlayerLeftEvent::Accept(GameEventVisitor& visitor) {
  visitor.Visit(*this);
}

bool PlayerLeftEvent::operator==(const PlayerLeftEvent& event) const {
  return reason_ == event.reason_;
}
}
}
