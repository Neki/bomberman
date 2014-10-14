
#include "GameEngine.h"



GameEngine::GameEngine()
{
  world_ = new World(80, 40);

}

void GameEngine::startGame() {

  while (true) {
    update(t)
  }

}


bool addEntity(Entity* entity){
  if(world_->isWalkable(entity->GetPosition()))
  {
    world_->addEntiry(entity);
    return true;
  }
  else{
    return false;
  }
}

std::weak_ptr<World> GameEngine::GetWorld() const {
  return weak_ptr<World> world_;
}

void GameEngine::update(int t) {
  challengeStrategies();
  simulate(t);
  sendGameState();
}
    
void GameEngine::challengeStrategies() {
  for(auto strategy : strategy_ ) {
    for (auto e : strategy->GetPendingEvents()) {
      e.visit(this);
    }
  }
}

void GameEngine::simulate(int t) {
  for(auto character : world_->GetCharacters) {
    character->update(t);
  }

  for(auto column : world_->GetEntities) {
    for(auto block : column) {
      for(auto entity : block) {
        entity->update(t);
      }
    }
  }
  
  // TODO : handle fire
  
  // TODO : remove destroyed entities
  
}

void GameEngine::sendGameState() {
  // TODO
}

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
}

void GameEngine::moveCharacter(int player_id, QPoint target) {

}
