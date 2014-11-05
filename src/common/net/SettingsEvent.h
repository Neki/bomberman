#ifndef SRC_COMMON_NET_SETTINGSEVENT_H_
#define SRC_COMMON_NET_SETTINGSEVENT_H_

#include "Event.h"

namespace common {
namespace net {

class SettingsEvent : public Event {

  public:
    SettingsEvent(quint32 id, quint32 timestamp);
    SettingsEvent(quint32 timestamp);

    void Serialize(QDataStream& stream) const;

    bool operator==(const SettingsEvent& event) const;

};

}
}

#endif
