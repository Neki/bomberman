#include "Fire.h"

namespace common {
namespace entity {

Fire::Fire(QPoint position, quint32 set_time)
  : Entity(position, false, false, "res/fire.svg"),
    set_time_(set_time) {
  disappearing_time_ = set_time_ + 300;
}

quint32 Fire::GetSetTime() const
{
  return set_time_;
}

quint32 Fire::GetDisappearingTime() const
{
  return disappearing_time_;
}

void Fire::Update(GameEngine* game_engine, int t)
/* Method to be called at every frame.
   t : duration of the frame in ms */
{
	(void) t;
  if (game_engine->GetTimestamp() >= disappearing_time_) {
    should_be_removed_ = true;
    return;
  }

  for (auto it = game_engine->GetWorld()->CharacterIteratorBegin(); it != game_engine->GetWorld()->CharacterIteratorEnd(); ++it) {
    if (((*it)->GetPositionF() - GetPositionF()).manhattanLength() < 0.8f) {
      (*it)->HitByFire(game_engine);
    }
  }

  for (auto it = game_engine->GetWorld()->IteratorAtBegin(position_); it != game_engine->GetWorld()->IteratorAtEnd(position_); ++it) {
    (*it)->HitByFire(game_engine);
  }

}

bool Fire::operator==(const Fire& other) const {
  return Entity::operator==(other) && set_time_ == other.set_time_ && disappearing_time_ == other.disappearing_time_;
}

void Fire::Serialize(QDataStream& stream) const {
  SerializeBaseEntity(stream, kFireId);
  stream << set_time_;
}

}
}

