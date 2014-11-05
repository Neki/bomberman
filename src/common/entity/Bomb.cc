
#include "Bomb.h"
#include "Fire.h"
#include "src/common/GameEngine.h"

namespace common {
namespace entity {

Bomb::Bomb(QPoint position, quint32 set_time, quint32 explosion_time, int power)
 :  Entity(position, true, false, "res/bomb.png"),
    set_time_(set_time),
    explosion_time_(explosion_time),
    power_(power) {
}

quint32 Bomb::GetSetTime() const {
	return set_time_;
}

quint32 Bomb::GetExplosionTime() const {
	return explosion_time_;
}

void Bomb::HitByFire(GameEngine* game_engine) {
  /* Called when entity is hit by fire. */
  explode(game_engine);
}

void Bomb::explode(GameEngine* game_engine) {
	game_engine->AddFireFromAtoB(GetPosition(), GetPosition() + QPoint(0, -power_));
	game_engine->AddFireFromAtoB(GetPosition(), GetPosition() + QPoint(power_, 0));
	game_engine->AddFireFromAtoB(GetPosition(), GetPosition() + QPoint(0, power_));
	game_engine->AddFireFromAtoB(GetPosition(), GetPosition() + QPoint(-power_, 0));

  // remove the bomb
  should_be_removed_ = true;
}

void Bomb::Update(GameEngine* game_engine, int t) {
/* Method to be called at every frame.
   t : duration of the frame in ms */
  (void) t;
  if ((quint32) QTime::currentTime().msec() >= this->GetExplosionTime()) {// TODO : change to use the game clock
    this->explode(game_engine);
  }
}

bool Bomb::operator==(const Bomb& other) const {
  return Entity::operator==(other)&& set_time_ == other.set_time_ && explosion_time_ == other.explosion_time_ && power_ == other.power_;
}

void Bomb::Serialize(QDataStream& stream) const {
  SerializeBaseEntity(stream, EntityId::kBombId);
  stream << set_time_;
  stream << explosion_time_;
  stream << (quint8) power_;
}

}
}
