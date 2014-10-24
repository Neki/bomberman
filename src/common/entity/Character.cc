
#include "Character.h"

#include <QPointF>

namespace common {
namespace entity {

Character::Character(QPoint position)
  : Entity(position, false, false, "res/default_character.png"),
    power_(1), // bomb power in tiles
    current_speed_(), // in tiles per second. might be temporary superior to the nominal speed
    speed_(), // nominal speed
    exact_position_(position),
    number_of_bombs_(1),
    bomb_delay_(300) {// TODO: correct
}

unsigned int Character::GetPower() const {
	return power_;
}

QPointF Character::GetCurrentSpeed() const {
	return current_speed_;
}

float Character::GetSpeed() const {
	return speed_;
}

QPointF Character::GetPositionF() const {
	return exact_position_;
}

unsigned int Character::GetNumberOfBombs() const {
	return number_of_bombs_;
}

int Character::GetBombDelay() const {
	return bomb_delay_;
}

void Character::moveTo(QPoint t, int speed) {
  (void) t;
  (void) speed;
}

void Character::HitByFire() {
  /* Called when entity is hit by fire. */
	should_be_removed_ = true;
}

void Character::Update(std::weak_ptr<GameEngine> game_engine, int t) {
/* Method to be called at every frame.
   t : duration of the frame in ms */
  (void) t;
	// TODO : Update position
}

}
}
