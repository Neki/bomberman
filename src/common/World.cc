
#include "World.h"

namespace common {

World::World(int width, int height)
  : game_engine_(),
    width_(width),
    height_(height) {
  (void) width_;
  (void) height_;
}

std::weak_ptr<GameEngine> World::GetGameEngine() const {
  return game_engine_;
}

}