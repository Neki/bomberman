
#include "Wall.h"

namespace common {
namespace entity {

Wall::Wall(std::weak_ptr<World> world, QPoint position) : Entity(world, position, true)
{

}


void Wall::HitByFire() {
  /* Called when entity is hit by fire. */
}

}
}