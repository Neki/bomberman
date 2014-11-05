#include "MoveEvent.h"
#include "EventId.h"

namespace common {
namespace net {

MoveEvent::MoveEvent(QPoint position, QPoint destination, Direction direction, quint32 id, quint32 timestamp) :
    InGameEvent(id, timestamp),
    position_(position),
    direction_(direction),
    destination_(destination) {
}

MoveEvent::MoveEvent(QPoint position, QPoint destination, Direction direction, quint32 timestamp) :
    InGameEvent(timestamp),
    position_(position),
    direction_(direction),
    destination_(destination) {
}

Direction MoveEvent::GetDirection() const {
  return direction_;
}

QPoint MoveEvent::GetPosition() const {
  return position_;
}

QPoint MoveEvent::GetDestination() const {
  return destination_;
}

void MoveEvent::Serialize(QDataStream& stream) const {
  SerializeBaseEvent(stream, EventId::kMoveEventId);
  stream << GetPosition();
  stream << GetDestination();
  stream << (quint8) GetDirection();
}

void MoveEvent::Accept(GameEventVisitor& visitor) {
  visitor.Visit(*this);
}

bool MoveEvent::operator==(const MoveEvent& event) const {
  return Event::operator==(event) && direction_ == event.direction_ && position_ == event.position_;
}

}
}
