#ifndef SRC_COMMON_GAMETIMER_H_
#define SRC_COMMON_GAMETIMER_H_

#include <QTime>

namespace common {

/**
 * A unique source of timestamps for a running game.
 * Note: if the system clock settings are changed during the game, this class
 * may return invalid results.
 * Assignment and copy constructors are private as to prevent inadvertently
 * using several timestamp references for the same game.
 */
class GameTimer {

  public:
    GameTimer();
    void StartGame();
    quint32 GetTimestamp();

  private:
    QTime timer_;
    GameTimer operator=(const GameTimer& other);
    GameTimer(const GameTimer& other);

};

}

#endif
