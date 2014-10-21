#ifndef SRC_COMMON_NET_INGAMEEVENT_H_
#define SRC_COMMON_NET_INGAMEEVENT_H_

#include "Event.h"

namespace common {
namespace net {

class InGameEvent : public Event {
  public:
    InGameEvent(quint32 id, quint64 timestamp);
    InGameEvent(quint64 timestamp);
    virtual ~InGameEvent();

};

}

}

#endif

