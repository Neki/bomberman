#include "PlayerLeftEvent.h"
#include "EventId.h"

namespace common {
namespace net {

PlayerLeftEvent::PlayerLeftEvent(QuitReason reason, quint32 id, quint64 timestamp)
  : InGameEvent(id, timestamp),
    reason_(reason) {}

QuitReason PlayerLeftEvent::GetReason() const {
  return reason_;
}

void PlayerLeftEvent::Serialize(QDataStream& stream) const {
  stream << (quint32) EventId::kPlayerLeftEvent;
  SerializeBaseEvent(stream);
  stream << GetReason();
}

bool PlayerLeftEvent::operator==(const PlayerLeftEvent& event) const {
  return reason_ == event.reason_;
}
}
}
