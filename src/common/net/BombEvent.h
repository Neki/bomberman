#ifndef SRC_COMMON_NET_BOMBEVENT_H_
#define SRC_COMMON_NET_BOMBEVENT_H_

#include <QPoint>

#include "InGameEvent.h"

namespace common {
namespace net {

class BombEvent : public InGameEvent {

  public:
    BombEvent(QPoint position, quint8 character_id, quint32 id, quint32 timestamp);
    BombEvent(QPoint position, quint8 character_id, quint32 timestamp);
    QPoint GetPosition() const;

    void Serialize(QDataStream& stream) const;

    void Accept(GameEventVisitor& visitor) override;

    bool operator==(const BombEvent& event) const;

  private:
    QPoint position_;

};

}
}

#endif
