#ifndef SRC_COMMON_NET_PLAYERJOINEDEVENT_H_
#define SRC_COMMON_NET_PLAYERJOINEDEVENT_H_

#include <QString>

#include "Event.h"

namespace common {
namespace net {

class PlayerJoinedEvent : public Event {

  public:
    PlayerJoinedEvent(QString player_name, quint32 id, quint32 timestamp);
    PlayerJoinedEvent(QString player_name, quint32 timestamp);
    QString GetPlayerName() const;

    void Serialize(QDataStream& stream) const;

    bool operator==(const PlayerJoinedEvent& event) const;

  private:
    QString player_name_;

};

}
}

#endif /* end of include guard: SRC_SERVER_NET_PLAYERJOINEDEVENT_H_ */
