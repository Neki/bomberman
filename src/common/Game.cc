#include "Game.h"
#include <QObject>
#include <stdexcept>

namespace common {

Game::Game()
  : players_(),
    max_id_used(0) {

}

int Game::AddPlayer(std::shared_ptr<Player> player) {
  max_id_used += 1;
  int player_id = max_id_used;
  players_.push_back(std::shared_ptr<Player>(player));
  return player_id;
}

std::weak_ptr<Player> Game::GetPlayer(int id) {
  for (auto it = players_.cbegin(); it != players_.cend(); ++it) {
    if ((*it)->GetId() == id) {
      return std::weak_ptr<Player>(*it);
    }
  }

  throw std::out_of_range("Unknown player id");
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
