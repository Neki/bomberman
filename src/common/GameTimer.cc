#include "GameTimer.h"

namespace common {

GameTimer::GameTimer() {
}

void GameTimer::StartGame() {
  timer_.start();
}

quint32 GameTimer::GetTimestamp() {
  //TODO(faucon_b): throw an exception if the game is not currently running?
  return timer_.elapsed();
}

}
