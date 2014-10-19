#ifndef SRC_COMMON_NET_EVENTID_H_
#define SRC_COMMON_NET_EVENTID_H_

namespace common {
namespace net {

enum EventId {
  kUnknownEventId = 0,
  kBombEventId,
  kMoveEventId,
  kPlayerJoinedEvent,
  kPlayerLeftEvent,
  kSetAdminEvent,
  kSettingsEvent
};

}
}

#endif

