#ifndef SRC_COMMON_GAME_H_
#define SRC_COMMON_GAME_H_

#include <QObject>
#include <vector>
#include "Player.h"

namespace common
{
    class Game : public QObject
    {
    public:
        std::vector<Player*> Game::getPlayers();
    protected:
        std::vector<Player*> players_;
    };
}
#endif
