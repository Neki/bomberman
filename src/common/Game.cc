#include "Game.h"
#include <cassert>

namespace common {

Game::Game()
  : players_(),
    game_engine_(nullptr),
    started_(false) {

}

void Game::AddPlayer(std::shared_ptr<Player> player) {
  assert(!started_);
  players_.push_back(std::shared_ptr<Player>(player));

  for (auto it = players_.cbegin(); it != players_.cend(); ++it) {
    assert((*it)->GetId() != player->GetId());
  }

}

std::weak_ptr<Player> Game::GetPlayer(int id) {
  for (auto it = players_.cbegin(); it != players_.cend(); ++it) {
    if ((*it)->GetId() == id) {
      return std::weak_ptr<Player>(*it);
    }
  }
  assert(false);
}

int Game::GetPlayersCount() {
  return (int) players_.size();
}

void Game::Start() {
  assert(!started_);
  game_engine_ = std::unique_ptr<GameEngine>();
  for (auto it = players_.cbegin(); it != players_.cend(); ++it) {
    game_engine_->AddPlayer(*it);
  }
  started_ = true;
  game_engine_->StartGame();
}

void Game::End() {
  assert(started_);
  started_ = false;
  game_engine_.release();
}

}
