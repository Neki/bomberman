#ifndef SRC_SERVER_WORLD_H_
#define SRC_SERVER_WORLD_H_

#include "GameEngine.h"
#include <memory>

namespace common {

class World {
  public:
    World(int width, int height);

    std::weak_ptr<GameEngine> GetGameEngine();
    
  private:
    std::weak_ptr<GameEngine> game_engine_;
    int width_;
    int height_;
};

}

#endif