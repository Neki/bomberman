#ifndef SRC_COMMON_NET_PLAYERLEFTEVENT_H_
#define SRC_COMMON_NET_PLAYERLEFTEVENT_H_

#include "InGameEvent.h"
#include "QuitReason.h"
#include "GameEventVisitor.h"

namespace common {
namespace net {

class PlayerLeftEvent : public InGameEvent {

  public:
    PlayerLeftEvent(QuitReason reason, quint32 id, quint32 timestamp);
    PlayerLeftEvent(QuitReason reason, quint32 timestamp);
    QuitReason GetReason() const;

    void Serialize(QDataStream& stream) const;

    void Accept(GameEventVisitor& visitor) override;

    bool operator==(const PlayerLeftEvent& event) const;

  private:
    QuitReason reason_;

};

}
}

#endif /* end of include guard: SRC_SERVER_NET_PLAYERLEFTEVENT_H_ */
