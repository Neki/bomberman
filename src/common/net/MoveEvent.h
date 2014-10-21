#ifndef SRC_COMMON_NET_MOVEMENTEVEVENT_H_
#define SRC_COMMON_NET_MOVEMENTEVEVENT_H_

#include <QPoint>

#include "InGameEvent.h"
#include "src/common/Direction.h"

namespace common {
namespace net {

class MoveEvent : public InGameEvent {

  public:
    MoveEvent(QPoint position, Direction getDirection, quint32 id, quint64 timestamp);
    Direction GetDirection() const;
    QPoint GetPosition() const;

    void Serialize(QDataStream& stream) const;

    bool operator==(const MoveEvent& event) const;

  private:
    QPoint position_;
    Direction direction_;

};

}
}

#endif /* end of include guard: SERVER_NETWORK_MOVEMENTEVEVENT_H_ */
