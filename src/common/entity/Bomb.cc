
#include "Bomb.h"
#include "Fire.h"
#include "src/common/GameEngine.h"

namespace common {
namespace entity {

  Bomb::Bomb(World* world, QPoint position, std::weak_ptr<Character> bomber) :
  Entity(world, position, true, false),
  bomber_(bomber)
{
  set_time_ = QTime::currentTime(); // TODO : change to use the game clock
  std::shared_ptr<Character> s_bomber(bomber_.lock());
  if (s_bomber) {
	explosion_time_ = set_time_.addMSecs(s_bomber->GetBombDelay());
	power_ = s_bomber->GetPower(); // in tiles;
  }
}

std::weak_ptr<Character> Bomb::GetBomber() const
{
	return bomber_;
}

QTime Bomb::GetSetTime() const
{
	return set_time_;
}

QTime Bomb::GetExplosionTime() const
{
	return explosion_time_;
}

void Bomb::HitByFire() {
  /* Called when entity is hit by fire. */
  explode();
}

void Bomb::explode()
{
  std::shared_ptr<World> s_world(GetWorld().lock());
  if (s_world) {
	std::shared_ptr<GameEngine> s_game_engine(s_world->GetGameEngine().lock());
	if (s_game_engine) {
	  s_game_engine->AddFireFromAtoB(GetPosition(), GetPosition() + QPoint(0, -power_));
	  s_game_engine->AddFireFromAtoB(GetPosition(), GetPosition() + QPoint(power_, 0));
	  s_game_engine->AddFireFromAtoB(GetPosition(), GetPosition() + QPoint(0, power_));
	  s_game_engine->AddFireFromAtoB(GetPosition(), GetPosition() + QPoint(-power_, 0));
	} else {
	  // TODO: Log errors
	}
  } else {
	  // TODO: Log errors
  }  

  // remove the bomb
  should_be_removed_ = true;
}

void Bomb::Update(int t)
/* Method to be called at every frame.
   t : duration of the frame in ms */
{
  (void) t;
  if (QTime::currentTime() >= this->GetExplosionTime()) {// TODO : change to use the game clock
    this->explode();
  }
}

}
}
