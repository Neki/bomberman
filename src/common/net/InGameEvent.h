#ifndef SRC_COMMON_NET_INGAMEEVENT_H_
#define SRC_COMMON_NET_INGAMEEVENT_H_

#include <QDataStream>
#include "EventId.h"
#include "GameEventVisitor.h"

namespace common {
namespace net {

class InGameEvent {
  public:
    InGameEvent(quint8 character_id, quint32 id, quint32 timestamp);
    InGameEvent(quint8 character_id, quint64 timestamp);
    virtual ~InGameEvent();

    quint8 GetCharacterId() const;
    void SetId(quint32 id);
    quint32 GetId() const;
    quint32 GetTimestamp() const;

    virtual void Serialize(QDataStream& stream) const = 0;

    virtual void Accept(GameEventVisitor& visitor) = 0;

  protected:
    /**
     * Serialize to @a stream the base data of the event: client version, id,
     * timestamp. Intended to be called by the derived classes in their
     * implementation of Serialize.
     */
    void SerializeBaseInGameEvent(QDataStream& stream, EventId event_id) const;
    bool operator==(const InGameEvent& other) const;

  private:
    quint8 character_id_;
    quint32 id_;
    quint32 timestamp_;



};

QDataStream& operator<<(QDataStream& stream, const InGameEvent& event);

}
}

#endif

