#ifndef SRC_COMMON_PLAYER_H_
#define SRC_COMMON_PLAYER_H_

#include <QObject>
#include <memory>
#include "Strategy.h"

namespace common {
    class Player {
    public:
        Player(int id, QString name);
        int GetId() const;
        QString GetName() const;
        int GetScore() const;
        int AddScore(int score_to_add);
        int SubstractScore(int score_to_substract);
        Strategy* GetStrategy();

    protected:
        int id_;
        QString name_;
        int score_;
        std::unique_ptr<Strategy> strategy_;
    };
}
#endif
