#include "MoveEvent.h"
#include "EventId.h"

namespace common {
namespace net {

MoveEvent::MoveEvent(QPoint position, Direction direction, quint32 id, quint64 timestamp) :
    Event(id, timestamp),
    position_(position),
    direction_(direction) {
}

Direction MoveEvent::GetDirection() const {
  return direction_;
}

QPoint MoveEvent::GetPosition() const {
  return position_;
}

void MoveEvent::Serialize(QDataStream& stream) const {
  stream << (quint32) EventId::kMoveEventId;
  SerializeBaseEvent(stream);
  stream << this->GetPosition();
  stream << this->GetDirection();
}

bool MoveEvent::operator==(const MoveEvent& event) const {
  return Event::operator==(event) && direction_ == event.direction_ && position_ == event.position_;
}

}
}
