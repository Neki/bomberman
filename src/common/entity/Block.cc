
#include "Block.h"

namespace common {
namespace entity {

Block::Block(QPoint position) :
  Entity(position, true, true, "res/block.png") {

}

void Block::Update(std::weak_ptr<GameEngine> game_engine, int t) {
  (void)t;
}

void Block::HitByFire() {
  /* Called when entity is hit by fire. */
  // TODO : add bonus creation
  should_be_removed_ = true;
}


}
}