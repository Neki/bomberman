
#include "Bomb.h"
#include "Fire.h"

namespace common {
namespace entity {

Bomb::Bomb(std::weak_ptr<World> world, QPoint position, std::weak_ptr<Character> bomber):
  Entity(world, position, true),
  bomber_(bomber)
{
  set_time_ = QTime::current_time(); // TODO : change to use the game clock
  explosion_time = set_time_ + bomber_->GetBombDelay_();
  power_ = bomber_->GetPower_(); // in tiles;
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

virtual void Bomb::HitByFire() {
  /* Called when entity is hit by fire. */
  explode();
}

void Bomb::explode()
{
  // Add fire on the world's grid
  GetWorld()->AddEntity(Fire(GetWorld(), GetPosition()));
  for (unsigned int i = 1 ; i <= power_ ; i++)
  {
    // TODO: correct this part of the code
    // Walls should stop fire propagation
    GetWorld()->AddEntity(make_shared<Fire>(GetWorld(), GetPosition()+QPoint(0,-1)));
    GetWorld()->AddEntity(make_shared<Fire>(GetWorld(), GetPosition()+QPoint(1,0)));
    GetWorld()->AddEntity(make_shared<Fire>(GetWorld(), GetPosition()+QPoint(0,1)));
    GetWorld()->AddEntity(make_shared<Fire>(GetWorld(), GetPosition()+QPoint(-1,0)));
  }

  // remove the bomb
  should_be_removed_ = true;
}

virtual void Bomb::Update(int t)
/* Method to be called at every frame.
   t : duration of the frame in ms */
{
  if (QTime::current_time() >= GetExplosionTime()) {// TODO : change to use the game clock
    explode();
  }
}

}
}
