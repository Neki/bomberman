
#include "Character.h"
#include <cmath>
#include <QPointF>

namespace common {
namespace entity {

Character::Character(QPoint position, int power, float speed, unsigned int number_of_bombs)
  : Entity(position, false, false, "res/default_character.png"),
    power_(power), // bomb power in tiles
    current_speed_(), // in tiles per second. might be temporary superior to the nominal speed
    speed_(speed), // nominal speed
    exact_position_(position),
    number_of_bombs_(1),
    bomb_delay_(300), // TODO: correct
    moving_(false),
    target_time_() {

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

bool Character::MoveTo(std::weak_ptr<GameEngine> game_engine, QPoint target) {
  if (moving_) {
    return false;
  } else {
    std::shared_ptr<GameEngine> game_engine_shared_ptr(game_engine.lock());
    if (game_engine_shared_ptr) {
      moving_ = true;
      position_ = target;
      float remaining_distance = DistanceBetween(QPointF(position_), exact_position_);
      target_time_ = game_engine_shared_ptr->GetTimestamp() + remaining_distance * speed_;
      return true;
    } else {
      return false;
    }
  }
}

void Character::HitByFire(std::weak_ptr<GameEngine> game_engine) {
  /* Called when entity is hit by fire. */
  (void) game_engine;
	should_be_removed_ = true;
}

float Character::DistanceBetween(QPointF a, QPointF b) {
  float x2 = (a.x() - b.x()) * (a.x() - b.x());
  float y2 = (a.y() - b.y()) * (a.y() - b.y());
  return sqrt(x2 + y2);
}

void Character::Update(std::weak_ptr<GameEngine> game_engine, int t) {
/* Method to be called at every frame.
   t : duration of the frame in ms */
  (void) game_engine;
  (void) t;

  float const max_speed = 1.5f;
  float remaining_distance = DistanceBetween(QPointF(position_), exact_position_);
  float current_speed_norm = 0.0f;

  std::shared_ptr<GameEngine> game_engine_shared_ptr(game_engine.lock());
  if (game_engine_shared_ptr) {
    quint32 current_time = game_engine_shared_ptr->GetTimestamp();
    if (current_time >= target_time_) {
      current_speed_norm = speed_ * max_speed;
    }
    else {
      current_speed_norm = fmax(speed_, fmin(speed_ * max_speed, remaining_distance / (current_time - target_time_)));
    }

    if (remaining_distance < current_speed_norm*t) {
      exact_position_ = QPointF(position_);
      current_speed_ = QPointF();
      moving_ = false;
    }
    else {
      current_speed_ = current_speed_norm * (position_ - exact_position_);
      exact_position_ += current_speed_ * t;
    }
  }
  else {
    
  }
  
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
