#include "Bonus.h"

namespace common {
namespace entity {

Bonus::Bonus(QPoint position, QString texture_path) :
  Entity(position, false, false, texture_path)
{

}

void Bonus::Update(std::weak_ptr<GameEngine> game_engine, int t) {
  (void)game_engine;
  (void)t;
}

void Bonus::HitByFire(std::weak_ptr<GameEngine> game_engine) {
  /* Called when entity is hit by fire. */
  // The bonus is not yet destroyed by fire
  (void)game_engine;
}

}
}
