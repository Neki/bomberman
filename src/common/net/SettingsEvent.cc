#include "SettingsEvent.h"
#include "EventId.h"

namespace common {
namespace net {

SettingsEvent::SettingsEvent(quint32 id, quint64 timestamp)
  : Event(id, timestamp) {}

void SettingsEvent::Serialize(QDataStream& stream) const {
  SerializeBaseEvent(stream, EventId::kSettingsEvent);
  // TODO when the settings event is completely defined
}

bool SettingsEvent::operator==(const SettingsEvent& event) const {
  return Event::operator==(event);
}

}
}
