#ifndef SRC_CLIENT_NET_NETWORKMANAGER_H_
#define SRC_CLIENT_NET_NETWORKMANAGER_H_

#include <memory>
#include <QObject>
#include <QHostAddress>
#include <QThread>
#include "src/common/net/Event.h"
#include "NetworkWorker.h"

using namespace common::net;

namespace net {

  enum NetworkState {
    kNotConnected, kInLobby, kInGame
  };

  class NetworkManager : public QObject {
    Q_OBJECT

    public:
      //void BroadcastGameState(const& World world);
      NetworkManager(QHostAddress server_address, quint16 server_port, quint16 client_port);
      void RunGame();
      void StopGame();
      void SendEvent(std::unique_ptr<Event> event);
      NetworkState GetState();

    private:
      QHostAddress server_address_;
      quint16 server_port_;
      quint16 client_port_;
      quint16 client_id_; // TODO initialize client_id when connecting to a lobby
      std::unique_ptr<NetworkWorker> game_worker_;
      NetworkState state_;

      QThread game_worker_thread_;

  };

}

#endif
