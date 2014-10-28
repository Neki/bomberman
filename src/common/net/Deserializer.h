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

#include "src/common/entity/EntityId.h"
#include "src/common/entity/Block.h"
#include "src/common/entity/Bomb.h"
#include "src/common/entity/Bonus.h"
#include "src/common/entity/Character.h"
#include "src/common/entity/Fire.h"
#include "src/common/entity/Wall.h"

using namespace common::entity;

namespace common {
namespace net {

/**
 * For internal use by the Deserializer class.
 */
struct BaseEventData {
  quint32 id;
  quint32 timestamp;
};

/**
 * Internal use by the Deserializer class
 */
struct BaseEntityData {
  quint32 id;
  quint32 temp_id;
  QPoint position;
};

/**
 * Provides static methods to deserialize events and entities. Part of the common library
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

    static EntityId GetNextEntityId(QDataStream& stream);
    static Block DeserializeBlock(QDataStream& stream);
    static Bomb DeserializeBomb(QDataStream& stream);
    static Bonus DeserializeBonus(QDataStream& stream);
    static Character DeserializeCharacter(QDataStream& stream);
    static Fire DeserializeFire(QDataStream& stream);
    static Wall DeserializeWall(QDataStream& stream);


  private:
    static BaseEventData DeserializeBaseEvent(QDataStream& stream);
    static BaseEntityData DeserializeBaseEntity(QDataStream& stream);

};

}
}


#endif
