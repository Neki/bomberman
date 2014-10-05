#include "Game.h"

namespace common {
    int Game::AddPlayer(Player& player) {
        int player_id = GetPlayersCount();
        players_.insert(std::pair<int, Player*>(player_id, &player));

        return player_id;
    }

    Player* Game::GetPlayer(int id) {
        if (!players_.count(id)) {
            throw std::exception("Unknown player id: " + id);
        }

        return players_[id];
    }

    int Game::GetPlayersCount() {
        return players_.size();
    }

    void Game::Start() {
        // start the game !
    }

    void Game::End() {
        // end the game !
    }
}
