#ifndef SRC_COMMON_NET_SETADMINEVENT_H_
#define SRC_COMMON_NET_SETADMINEVENT_H_

#include "Event.h"

namespace common {
namespace net {

class SetAdminEvent : public Event {

  public:
    SetAdminEvent(quint32 id, quint64 timestamp);

    void Serialize(QDataStream& stream) const;

    bool operator==(const SetAdminEvent& event) const;

};

}
}

#endif
