#ifndef COMMON_GAME_H_
#define COMMON_GAME_H_

#include <QObject>
#include <vector>
#include "Player.h"

using namespace std;

namespace common
{
    class Game : public QObject
    {
    public:
        vector<Player*> Game::getPlayers();
    protected:
        vector<Player*> players_;
    };
}
#endif
