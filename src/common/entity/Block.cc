
#include "Block.h"

namespace common {
namespace entity {

Block::Block(QPoint position) :
  Entity(position, true, true, "res/block.png") {

}

void Block::Update(std::weak_ptr<GameEngine> game_engine, int t) {
  (void) game_engine;
  (void) t;
}

void Block::HitByFire(std::weak_ptr<GameEngine> game_engine) {
  /* Called when entity is hit by fire. */
  // TODO : add bonus creation
  (void) game_engine;
  should_be_removed_ = true;
}

void Block::Serialize(QDataStream& stream) const {
  SerializeBaseEntity(stream, EntityId::kBlockId); //nothing else to do
}

bool Block::operator==(const Block& other) const {
  return Entity::operator==(other);
}


}
}
