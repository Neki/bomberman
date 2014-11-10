#ifndef SRC_COMMON_GAME_H_
#define SRC_COMMON_GAME_H_

#include <vector>
#include "Player.h"
#include <memory>

namespace common {

class Game {
  public:
    std::weak_ptr<Player> GetPlayer(int id);
    int GetPlayersCount();
    void AddPlayer(std::shared_ptr<Player> player);
    /* Each player should have an unique ID ! */
    void Start();
    void End();
  private:
    std::vector<std::shared_ptr<Player> > players_;

};
}
#endif
