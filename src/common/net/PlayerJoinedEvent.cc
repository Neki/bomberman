#include "PlayerJoinedEvent.h"
#include "EventId.h"

namespace common {
namespace net {

PlayerJoinedEvent::PlayerJoinedEvent(QString player_name, quint32 id, quint64 timestamp) :
  Event(id, timestamp),
  player_name_(player_name) {
}

QString PlayerJoinedEvent::GetPlayerName() const {
  return player_name_;
}

void PlayerJoinedEvent::Serialize(QDataStream& stream) const {
  stream << (quint32) EventId::kPlayerJoinedEvent;
  SerializeBaseEvent(stream);
  stream << GetPlayerName();
}

bool PlayerJoinedEvent::operator==(const PlayerJoinedEvent& event) const {
  return Event::operator==(event) && event.player_name_ == player_name_;
}

}}
