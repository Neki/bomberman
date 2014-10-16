
#include "Character.h"

#include <QPointF>

namespace common {
namespace entity {

Character::Character(std::weak_ptr<World> world, QPoint position) :
  Entity(world, position, false),
  position_(position), // TODO: correct
  power_(1), // bomb power in tiles
  current_speed_(), // in tiles per second. might be temporary superior to the nominal speed
  speed_(), // nominal speed
  number_of_bombs_(1)
{

}

unsigned int Character::GetPower() const
{
	return power_;
}

QPointF Character::GetCurrentSpeed() const
{
	return current_speed_;
}

float Character::GetSpeed() const
{
	return speed_;
}

QPointF Character::GetPosition() const
{
	return position_;
}

unsigned int Character::GetNumberOfBombs() const
{
	return number_of_bombs_;
}

void Character::moveTo(QPoint t, int speed)
{

}

void Character::HitByFire() {
  /* Called when entity is hit by fire. */
	should_be_removed_ = true;
}

virtual void Character::Update(unsigned int t)
/* Method to be called at every frame.
   t : duration of the frame in ms */
{
	// TODO : Update position
}

}
}
