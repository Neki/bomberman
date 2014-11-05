#ifndef SRC_COMMON_NET_INGAMEEVENT_H_
#define SRC_COMMON_NET_INGAMEEVENT_H_

#include "Event.h"
#include "GameEventVisitor.h"

namespace common {
namespace net {

class InGameEvent : public Event {
  public:
    InGameEvent(quint32 id, quint32 timestamp);
    InGameEvent(quint64 timestamp);
    virtual ~InGameEvent();

    virtual void Accept(GameEventVisitor& visitor) = 0;

};

}

}

#endif

