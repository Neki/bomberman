#include "NetworkManager.h"
#include "easylogging++.h"

namespace net {

NetworkManager::NetworkManager(QHostAddress server_address, quint16 server_port, quint16 client_port, std::shared_ptr<common::GameTimer> game_timer)
 :  server_address_(server_address),
    server_port_(server_port),
    client_port_(client_port),
    game_timer_(game_timer) {

}

void NetworkManager::RunGame() {
  game_worker_.reset(new NetworkWorker(client_id_, server_address_, server_port_, client_port_, game_timer_));
  game_worker_->moveToThread(&game_worker_thread_);
  game_worker_thread_.start();
  state_ = NetworkState::kInGame;
}

void NetworkManager::StopGame() {
  if(state_ == NetworkState::kInGame) {
    game_worker_thread_.quit();
    game_worker_thread_.wait();
    LOG(INFO) << "Network worker thread killed";
  }
}

void NetworkManager::SendEvent(std::unique_ptr<Event> event) {
  game_worker_->AddEvent(std::move(event));
}

NetworkState NetworkManager::GetState() {
  return state_;
}


}
