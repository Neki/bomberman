#include "GameEngine.h"
#include <vector>

namespace common {

  GameEngine::GameEngine(std::vector<Player> players)
  : //InGameEventVisitor(),
    maxDuration(),
    world_(80, 40),
    strategies_() {
  
}


void GameEngine::startGame() {
  while (true) {
    update(50);
  }
}

bool GameEngine::addEntity(std::unique_ptr<entity::Entity> e) {
  if (world_->IsWalkable(e->GetPosition()))
  {
    world_->AddItem(std::move(e));
    return true;
  }
  else{
    return false;
  }
}

World* GameEngine::GetWorld() const {
  return world_.get();
}

void GameEngine::AddFireFromAtoB(QPoint a, QPoint b) {
  if (a.x() == b.x()) {
    if (a.y() <= b.y()) {
      for (int y = a.y(); y <= b.y(); y++) {
        QPoint c(a.x(), y);
        if (world_->StopsFire(c)) {
          return;
        } else {
          addEntity(std::unique_ptr<entity::Fire>( new entity::Fire(world_.get(), c)));
        }
      }
    }
    else {
      for (int y = a.y(); y >= b.y(); y--) {
        QPoint c(a.x(), y);
        if (world_->StopsFire(c)) {
          return;
        }
        else {
          addEntity(std::unique_ptr<entity::Fire>(new entity::Fire(world_.get(), c)));
        }
      }
    }
  } else if (a.y() == b.y()) {
    if (a.x() <= b.x()) {
      for (int x = a.x(); x <= b.x(); x++) {
        QPoint c(x, a.y());
        if (world_->StopsFire(c)) {
          return;
        }
        else {
          addEntity(std::unique_ptr<entity::Fire>(new entity::Fire(world_.get(), c)));
        }
      }
    }
    else {
      for (int x = a.x(); x >= b.x(); x--) {
        QPoint c(x, a.y());
        if (world_->StopsFire(c)) {
          return;
        }
        else {
          addEntity(std::unique_ptr<entity::Fire>(new entity::Fire(world_.get(), c)));
        }
      }
    }
  } else {
    // TODO : log error
  }
}

void GameEngine::update(int t) { // t in ms. t is the duration of the frame
  challengeStrategies();
  simulate(t);
  sendGameState();
}

void GameEngine::challengeStrategies() {

}

void GameEngine::simulate(int t) { // t in ms. t is the duration of the frame

}

void GameEngine::sendGameState() {
  // TODO
}

/*bool GameEngine::accept(BombEvent& e) {

}

bool GameEngine::accept(MoveEvent& e) {

}*/

void GameEngine::moveCharacter(int player_id, QPoint target) {
  
}

void GameEngine::challengeStrategies() {
  /*for (auto strategy : strategy_) {
    for (auto e : strategy->GetPendingEvents()) {
      e.visit(this);
    }
  }*/
}

void GameEngine::simulate(int t) {
 /* for (auto character : world_->GetCharacters) {
    character->update(t);
  }
  for (auto column : world_->GetEntities) {
    for (auto block : column) {
      for (auto entity : block) {
        entity->update(t);
      }
    }
  }
  // TODO : handle fire
  // TODO : remove destroyed entities
  */
}

/*
bool GameEngine::accept(ClientEvent<BombEvent>& client_event) {
  int id = client_event.getClientId();
  // TODO : Check if value is ok
  BombEvent e = client_event.getEventData();
  // TODO : checks on the character
  //addEntity(Bomb(...));
}
bool GameEngine::accept(ClientEvent<MoveEvent>& client_event) {
  int id = client_event.getClientId();
  // TODO : Check if value is ok
  MoveEvent e = client_event.getEventData();
  //moveCharacter(id,);
}*/

}