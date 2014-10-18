
#include "World.h"

World::World(int width, int height) :
width_(width),
height_(height),
game_engine_(nullptr)
{
  
}

std::weak_ptr<GameEngine> World::GetGameEngine() {
  return game_engine_;
}