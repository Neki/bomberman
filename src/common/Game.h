#ifndef SRC_COMMON_GAME_H_
#define SRC_COMMON_GAME_H_

#include <vector>
#include <map>
#include "Player.h"

namespace common {
    class Game {
    public:
        std::map<int, Player*> GetPlayers();
        Player* GetPlayer(int id);
        int GetPlayersCount();
        int AddPlayer(Player& player);
        void Start();
        void End();
    protected:
        std::map<int, Player*> players_;
    };
}
#endif
