#ifndef SRC_COMMON_PLAYER_H_
#define SRC_COMMON_PLAYER_H_

#include <QObject>

namespace common {
    class Player {
    public:
        Player(int id);
        Player(QString name);
        int id();
        QString name();
        int score();
        int AddScore(int score_to_add);
        int SubstractScore(int score_to_substract);

    protected:
        int id_;
        QString name_;
        int score_;
    };
}
#endif
