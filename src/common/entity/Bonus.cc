#include "Bonus.h"

namespace common {
namespace entity {

Bonus::Bonus(std::weak_ptr<World> world, QPoint position, QString texture_path) :
  Entity(world, position, false, false, texture_path)
{

}

void Bonus::Update(int t) {
  (void)t;
}

void Bonus::HitByFire () {
  /* Called when entity is hit by fire. */
  // The bonus is not yet destroyed by fire
}

}
}
