#ifndef SRC_COMMON_PLAYER_H_
#define SRC_COMMON_PLAYER_H_

#include <QObject>

namespace common
{
    class Player : public QObject
    {
    public:
        int Player::getId();
        QString Player::getName();
        int Player::getScore();

    protected:
        int id_;
        QString name_;
        int score_;
    };
}
#endif
