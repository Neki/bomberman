#include "PlayerJoinedEvent.h"
#include "EventId.h"

namespace common {
namespace net {

PlayerJoinedEvent::PlayerJoinedEvent(QString player_name, quint32 id, quint32 timestamp) :
  Event(id, timestamp),
  player_name_(player_name) {
}

PlayerJoinedEvent::PlayerJoinedEvent(QString player_name, quint32 timestamp) :
  Event(timestamp),
  player_name_(player_name) {
}

QString PlayerJoinedEvent::GetPlayerName() const {
  return player_name_;
}

void PlayerJoinedEvent::Serialize(QDataStream& stream) const {
  SerializeBaseEvent(stream, EventId::kPlayerJoinedEvent);
  stream << GetPlayerName();
}

bool PlayerJoinedEvent::operator==(const PlayerJoinedEvent& event) const {
  return Event::operator==(event) && event.player_name_ == player_name_;
}

}}
