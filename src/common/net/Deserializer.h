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

struct BaseEventData {
  QString client_version;
  quint32 id;
  quint64 timestamp;
};

class Deserializer {

  public:
    static EventId GetNextEventId(QDataStream& stream);

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
