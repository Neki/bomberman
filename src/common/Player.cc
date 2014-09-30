#include "Player.h"
#include <QObject>

namespace common {
    Player::Player(int id) : id_(id), score_(0) {
    }

    Player::Player(QString name) : name_(name), score_(0) {
    }

    int Player::id() {
        return id_;
    }

    QString Player::name() {
        return name_;
    }

    int Player::score() {
        return score_;
    }

    int Player::AddScore(int score_to_add) {
        score_ += score_to_add;

        return score_;
    }

    int Player::SubstractScore(int score_to_substract) {
        return AddScore(-score_to_substract);
    }
}
