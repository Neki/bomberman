#include "Player.h"

namespace common {

Player::Player(int id, QString name)
  : id_(id),
    name_(name),
    score_(0),
    strategy_() {
}

int Player::GetId() const {
  return id_;
}

QString Player::GetName() const {
  return name_;
}

int Player::GetScore() const {
  return score_;
}

int Player::AddScore(int score_to_add) {
  score_ += score_to_add;
  return score_;
}

int Player::SubstractScore(int score_to_substract) {
  return AddScore(-score_to_substract);
}

Strategy* Player::GetStrategy() {
  return strategy_.get();
}

}
