#ifndef SRC_COMMON_NET_INGAMEEVENT_H_
#define SRC_COMMON_NET_INGAMEEVENT_H_

#include <QDataStream>
#include "Event.h"
#include "GameEventVisitor.h"

namespace common {
namespace net {

class InGameEvent : public Event {
  public:
    InGameEvent(quint8 character_id, quint32 id, quint32 timestamp);
    InGameEvent(quint8 character_id, quint64 timestamp);
    virtual ~InGameEvent();

    virtual void Accept(GameEventVisitor& visitor) = 0;

  protected:
    void SerializeBaseInGameEvent(QDataStream& stream, EventId event_id) const;
    bool operator==(const InGameEvent& other) const;

  private:
    quint8 character_id_;



};

}

}

#endif

