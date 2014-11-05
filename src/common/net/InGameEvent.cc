#include "InGameEvent.h"

namespace common {
namespace net {

InGameEvent::InGameEvent(quint32 id, quint32 timestamp)
  : Event(id, timestamp) {
}

InGameEvent::InGameEvent(quint64 timestamp)
  : Event(timestamp) {
}

InGameEvent::~InGameEvent() {}

}
}
