#ifndef SRC_COMMON_NET_MOVEMENTEVEVENT_H_
#define SRC_COMMON_NET_MOVEMENTEVEVENT_H_

#include <QPoint>

#include "InGameEvent.h"
#include "GameEventVisitor.h"
#include "src/common/Direction.h"

namespace common {
namespace net {

class MoveEvent : public InGameEvent {

  public:
    MoveEvent(QPoint position, QPoint destination, Direction direction, quint32 id, quint64 timestamp);
    Direction GetDirection() const;
    QPoint GetDestination() const;
    QPoint GetPosition() const;

    void Serialize(QDataStream& stream) const;

    void Accept(GameEventVisitor& visitor) override;

    bool operator==(const MoveEvent& event) const;

  private:
    QPoint position_;
    Direction direction_;
    QPoint destination_;

};

}
}

#endif /* end of include guard: SERVER_NETWORK_MOVEMENTEVEVENT_H_ */
