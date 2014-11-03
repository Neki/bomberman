#include "SetAdminEvent.h"
#include "EventId.h"

namespace common {
namespace net {

SetAdminEvent::SetAdminEvent(quint32 id, quint32 timestamp)
    : Event(id, timestamp) {}

SetAdminEvent::SetAdminEvent(quint32 timestamp)
    : Event(timestamp) {}

void SetAdminEvent::Serialize(QDataStream& stream) const {
  SerializeBaseEvent(stream, EventId::kSetAdminEvent);
}

bool SetAdminEvent::operator==(const SetAdminEvent& event) const {
  return Event::operator==(event);
}

}
}
