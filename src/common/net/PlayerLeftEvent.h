#ifndef SRC_COMMON_NET_PLAYERLEFTDEVENT_H_
#define SRC_COMMON_NET_PLAYERLEFTDEVENT_H_

#include "InGameEvent.h"
#include "QuitReason.h"

namespace common {
namespace net {

class PlayerLeftEvent : public InGameEvent {

  public:
    PlayerLeftEvent(QuitReason reason, quint32 id, quint64 timestamp);
    QuitReason GetReason() const;

    void Serialize(QDataStream& stream) const;

    bool operator==(const PlayerLeftEvent& event) const;

  private:
    QuitReason reason_;

};

}
}

#endif /* end of include guard: SRC_SERVER_NET_PLAYERLEFTEVENT_H_ */
