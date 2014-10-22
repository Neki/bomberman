#ifndef SRC_COMMON_NET_DESERIALIZER_H_
#define SRC_COMMON_NET_DESERIALIZER_H_

#include <QDataStream>
#include <memory>

#include "Event.h"
#include "EventId.h"
#include "BombEvent.h"
#include "MoveEvent.h"
#include "PlayerLeftEvent.h"
#include "PlayerJoinedEvent.h"
#include "SetAdminEvent.h"
#include "SettingsEvent.h"

namespace common {
namespace net {

/**
 * For internal use by the Deserializer class.
 */
struct BaseEventData {
  QString client_version;
  quint32 id;
  quint64 timestamp;
};

/**
 * Provides static methods to deserialize an event. Part of the common library
 * to make testing serialization and deserialization easier to test (as
 * everything is in one place).
 */
class Deserializer {

  public:
    /**
     * @return the event type of the next event serialized on the stream.
     *         Allows to choose which deserialization method to call next.
     *         (see the serialization tests for an example)
     */
    static EventId GetNextEventId(QDataStream& stream);

    /*
     * Deserialize the next event on the stream.
     * @return the next event on the stream. If the event could not be properly
     * deserialized, the returned pointer will be null.
     */
    static std::unique_ptr<InGameEvent> DeserializeInGameEvent(QDataStream& stream);

    static BombEvent DeserializeBombEvent(QDataStream& stream);
    static MoveEvent DeserializeMoveEvent(QDataStream& stream);
    static PlayerJoinedEvent DeserializePlayerJoinedEvent(QDataStream& stream);
    static PlayerLeftEvent DeserializePlayerLeftEvent(QDataStream& stream);
    static SetAdminEvent DeserializeSetAdminEvent(QDataStream& stream);
    static SettingsEvent DeserializeSettingsEvent(QDataStream& stream);

  private:
    static BaseEventData DeserializeBaseEvent(QDataStream& stream);

};

}
}


#endif
