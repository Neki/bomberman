
#include "Character.h"

#include <QPointF>

namespace common {
namespace entity {

Character::Character(QPoint position, int power, float speed, unsigned int number_of_bombs)
  : Entity(position, false, false, "res/default_character.png"),
    power_(power), // bomb power in tiles
    current_speed_(), // in tiles per second. might be temporary superior to the nominal speed
    speed_(speed), // nominal speed
    exact_position_(position),
    number_of_bombs_(number_of_bombs),
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

void Character::HitByFire(std::weak_ptr<GameEngine> game_engine) {
  /* Called when entity is hit by fire. */
  (void) game_engine;
	should_be_removed_ = true;
}

void Character::Update(std::weak_ptr<GameEngine> game_engine, int t) {
/* Method to be called at every frame.
   t : duration of the frame in ms */
  (void)game_engine;
  (void) t;
	// TODO : Update position
}

bool Character::operator==(const Character& other) const {
  return Entity::operator==(other) && power_ == other.power_ && number_of_bombs_ == other.number_of_bombs_ && bomb_delay_ == other.bomb_delay_;
  //TODO: better comparison using also the speed
}

void Character::Serialize(QDataStream& stream) const {
  SerializeBaseEntity(stream, kCharacterId);
  stream << power_;
  stream << speed_;
  stream << number_of_bombs_;
}

}
}
