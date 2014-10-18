#include "Fire.h"

#include <QTime>

namespace common {
namespace entity {

Fire::Fire(std::weak_ptr<World> world, QPoint position) :
  Entity(world, position, false, false)
{  
  set_time_ = QTime::current_time(); // TODO : change to use the game clock
  disappearing_time_ = set_time_ + 300;
}

QTime Fire::GetSetTime() const
{
  return set_time_;
}

QTime Fire::GetDisappearingTime() const
{
  return disappearing_time_;
}

virtual void Fire::Update(int t)
/* Method to be called at every frame.
   t : duration of the frame in ms */
{
    if (QTime::current_time() >= GetDisappearingTime()) {// TODO : change to use the game clock
      should_be_removed_ = true;
  }
}

}
}

