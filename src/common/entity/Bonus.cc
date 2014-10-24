#include "Bonus.h"

namespace common {
namespace entity {

  Bonus::Bonus(World* world, QPoint position) :
  Entity(world, position, false, false)
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
