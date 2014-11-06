#include "BombEvent.h"
#include "EventId.h"

namespace common {
namespace net {

BombEvent::BombEvent(QPoint position, quint8 character_id, quint32 id, quint32 timestamp)
    : InGameEvent(character_id, id, timestamp),
      position_(position) {
}

BombEvent::BombEvent(QPoint position, quint8 character_id, quint32 timestamp)
    : InGameEvent(character_id, timestamp),
      position_(position) {
}

QPoint BombEvent::GetPosition() const {
  return position_;
}

void BombEvent::Serialize(QDataStream& stream) const {
  SerializeBaseInGameEvent(stream, EventId::kBombEventId);
  stream << this->GetPosition();
}

void BombEvent::Accept(GameEventVisitor& visitor) {
  visitor.Visit(*this);
}

bool BombEvent::operator==(const BombEvent& event) const {
  return InGameEvent::operator==(event) && position_ == event.position_;
}

}
}
