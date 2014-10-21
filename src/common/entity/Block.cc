
#include "Block.h"

namespace common {
namespace entity {

  Block::Block(World* world, QPoint position) :
  Entity(world, position, true, true)
{

}

void Block::Update(int t) {
  (void)t;
}

void Block::HitByFire() {
  /* Called when entity is hit by fire. */
  // TODO : add bonus creation
  should_be_removed_ = true;
}


}
}