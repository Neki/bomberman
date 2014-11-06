#include "GameEngine.h"
#include "entity/Fire.h"
#include "entity/Character.h"
#include "entity/Bomb.h"
#include <cassert>

namespace common {

  GameEngine::GameEngine()
    : QObject(),
    net::GameEventVisitor(),
    max_duration_(10 * 60 * 1000), // 10 minutes
    players_(),
    world_(new World(79, 49)),
    game_timer_(),
    new_frame_timer_(new QTimer()),
    is_running_(false) {

}

GameEngine::~GameEngine() {
  new_frame_timer_->stop();
  disconnect(new_frame_timer_.get(), 0, 0, 0);
}

void GameEngine::AddPlayer(std::unique_ptr<Player> player) {
  players_.push_back(std::move(player));
  world_->AddCharacter(std::unique_ptr<entity::Character>());
}

void GameEngine::StartGame() {
  assert(!is_running_);
  if (is_running_) {
    return;
  }
  is_running_ = true;

  game_timer_.StartGame();
  connect(new_frame_timer_.get(), SIGNAL(timeout()), this, SLOT(Update(50)));
  new_frame_timer_->start(50);
}

bool GameEngine::AddEntity(std::unique_ptr<entity::Entity> e) {
  if ( !world_->CheckCoord(e->GetPosition()) ) {
    return false;
  }
  if ( e->IsSolid() && !world_->IsWalkable(e->GetPosition())) {
    return false;
  }
  return world_->AddItem(std::move(e));
}

World* GameEngine::GetWorld() const {
  return world_.get();
}

quint32 GameEngine::GetTimestamp() const {
  return game_timer_.GetTimestamp();
}

void GameEngine::AddFireFromAtoB(QPoint a, QPoint b) {
  assert(a.x() == b.x() || a.y() == b.y());
  quint32 currentTime = GetTimestamp();
  if (a.x() == b.x()) {
    if (a.y() <= b.y()) {
      for (int y = a.y(); y <= b.y(); y++) {
        QPoint c(a.x(), y);
        if (world_->StopsFire(c)) {
          return;
        } else {
          AddEntity(std::unique_ptr<entity::Fire>(new entity::Fire(c, currentTime)));
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
          AddEntity(std::unique_ptr<entity::Fire>(new entity::Fire(c, currentTime)));
        }
      }
    }
  } else if (a.y() == b.y()) {
    if (a.x() <= b.x()) {
      for (int x = a.x(); x <= b.x(); x++) {
        QPoint c(x, a.y());
        if (world_->StopsFire(c)) {
          return;
        } else {
          AddEntity(std::unique_ptr<entity::Fire>(new entity::Fire(c, currentTime)));
        }
      }
    } else {
      for (int x = a.x(); x >= b.x(); x--) {
        QPoint c(x, a.y());
        if (world_->StopsFire(c)) {
          return;
        } else {
          AddEntity(std::unique_ptr<entity::Fire>(new entity::Fire(c, currentTime)));
        }
      }
    }
  } else {
  // TODO : log error
  }
}

    
void GameEngine::Update(int t) {
 // t in ms. t is the duration of the frame
  ChallengeStrategies();
  Simulate(t);
  SendGameState();
}

void GameEngine::ChallengeStrategies() {
  for (auto player_it = players_.begin(); player_it != players_.end(); ++player_it) {
    /*for (auto e : player_it->get()->GetStrategy()->GetPendingEvents()) {
      e.Accept(this);
    }*/
  }
}

void GameEngine::Simulate(int t) {
 // t in ms. t is the duration of the frame
  for (auto it = world_->CharacterIteratorBegin() ; it != world_->CharacterIteratorEnd() ; ++it) {
    it->get()->Update(this, t);
  }
  
  for (int x = 0; x < world_->GetWidth() ; x++) {
    for (int y = 0; y < world_->GetWidth() ; y++) {
      QPoint a(x, y);
      for (auto it = world_->IteratorAtBegin(a) ; it != world_->IteratorAtEnd(a) ; ++it) {
        it->get()->Update(this, t);
      }

    }
  }

  // TODO : handle fire
  
  world_->removeEntities(); // Removes entities that should be removed

}


void GameEngine::SendGameState() {
  // TODO
}

void GameEngine::Visit(net::MoveEvent& event) {
  // TODO : Check if value is ok
  MoveCharacter(event.GetId(), event.GetDestination());
}

void GameEngine::Visit(net::BombEvent& event) {
  int id = event.GetId();
  // TODO : Check if value is ok
  QPoint position(event.GetPosition());
  quint32 current_time = game_timer_.GetTimestamp();
  quint32 explosion_time = current_time + 2500; // TODO : move this value
  int power = GetWorld()->GetCharacter(id)->GetPower();
  // TODO : checks if the character is near position
  AddEntity(std::unique_ptr<entity::Bomb>(new entity::Bomb(position, current_time, explosion_time, power)));
}

void GameEngine::Visit(net::PlayerLeftEvent& event) {
  (void) event;
}


void GameEngine::MoveCharacter(int player_id, QPoint target) {
  if (world_->IsWalkable(target)) {
    entity::Character* character = GetWorld()->GetCharacter(player_id);
    if (character) {
      character->MoveTo(this, target);
    }
  }
}

}
