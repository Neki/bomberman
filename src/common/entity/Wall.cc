
#include "Wall.h"

namespace common {
namespace entity {

  Wall::Wall(World* world, QPoint position) :
  Entity(world, position, true, true)
{

}

void Wall::Update(int t) {
  (void) t;
}

}
}