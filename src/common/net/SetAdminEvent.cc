#include "SetAdminEvent.h"
#include "EventId.h"

namespace common {
namespace net {

SetAdminEvent::SetAdminEvent(quint32 id, quint64 timestamp)
    : Event(id, timestamp) {}

void SetAdminEvent::Serialize(QDataStream& stream) const {
  stream << (quint32) EventId::kSetAdminEvent;
  SerializeBaseEvent(stream);
}

bool SetAdminEvent::operator==(const SetAdminEvent& event) const {
  return Event::operator==(event);
}

}
}