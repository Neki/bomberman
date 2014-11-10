#include "Game.h"
#include <QObject>
#include <stdexcept>
#include <cassert>

namespace common {

Game::Game()
  : players_(),
    game_engine_(nullptr) {

}

void Game::AddPlayer(std::shared_ptr<Player> player) {
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
  // start the game !
}

void Game::End() {
  // end the game !
}

}
