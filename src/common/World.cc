
#include "World.h"
#include "src/common/entity/Entity.h"
#include "src/common/entity/Character.h"
#include "GameEngine.h"

namespace common {


World::World(std::weak_ptr<GameEngine> game_engine, int width, int height)
  : game_engine_(game_engine),
    width_(width),
    height_(height),
    entities_(),
    characters_() {

}

std::weak_ptr<GameEngine> World::GetGameEngine() const {
  return game_engine_;
}

int World::GetWidth() const {
  return width_;
}

int World::GetHeight() const {
  return height_;
}

bool World::CheckCoord(QPoint p) const {
  return 0 <= p.x() && p.x() < width_ && 0 <= p.y() && p.y() < height_;
}

bool World::IsWalkable(QPoint p) const {
  // Returns true if a character can walk on this case
  if (!CheckCoord(p)) {
    return false;
  }

  for (unsigned int i = 0; i != entities_[p.x()][p.y()].size(); i++) {
    if (entities_[p.x()][p.y()][i]->IsSolid()){
      return false;
    }
  }

  return true;
}

bool World::StopsFire(QPoint p) const {
  // Returns true if the case stops fire propagation
  if (!CheckCoord(p)) {
    return true;
  }

  for (unsigned int i = 0; i != entities_[p.x()][p.y()].size(); i++) {
    if (entities_[p.x()][p.y()][i]->StopsFire()){
      return true;
    }
  }

  return false;
}

bool World::AddItem(std::unique_ptr<entity::Entity> entity) {
  // Adds an entity to the grid. Returns false if it fail.
  if (!CheckCoord(entity->GetPosition())){
    return false;
  }
  entities_[entity->GetPosition().x()][entity->GetPosition().y()].emplace_back(std::move(entity));
  return true;
}

bool World::AddCharacter(std::unique_ptr<entity::Character> character) {
  // Adds a character to characters_. Returns false if it fail.
  if (!CheckCoord(character->GetPosition())){
    return false;
  }
  characters_.emplace_back(std::move(character));
  return true;
}

void World::removeEntities() {
  // Removes entities that should be removed
  for (auto columns_it = entities_.begin(); columns_it != entities_.end(); ++ columns_it) {
    for (auto case_it = columns_it->begin(); case_it != columns_it->end(); ++case_it){
      for (auto i = case_it->begin(); i != case_it->end();){
        if ((*i)->GetShouldBeRemoved()){
          i = case_it->erase(i);
        } else {
          ++i;
        }
      }
    }
  }

}

}