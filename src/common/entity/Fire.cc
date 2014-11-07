#include "Fire.h"

#include <QTime>

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

void Fire::Update(std::weak_ptr<GameEngine> game_engine, int t)
/* Method to be called at every frame.
   t : duration of the frame in ms */
{
  (void)game_engine;
	(void) t;
  if ((quint32) QTime::currentTime().msec() >= disappearing_time_) {// TODO : change to use the game clock
    should_be_removed_ = true;
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

