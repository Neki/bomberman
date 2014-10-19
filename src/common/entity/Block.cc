
#include "Block.h"

namespace common {
namespace entity {

Block::Block(std::weak_ptr<World> world, QPoint position) :
  Entity(world, position, true, true)
{

}

Block::~Block() {

}

void Block::HitByFire() {
  /* Called when entity is hit by fire. */
  // TODO : add bonus creation
  should_be_removed_ = true;
}


}
}