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

  /**
   * Manages the communication with the server. This is the entry class for the
   * client network API.
   * @note for now, it is only capable of managing a game, not the lobby.
   * Internally, this class uses a separate thread. Most of the methods it
   * provides are non-blocking. Note that instances are not thread-safe.
   */
  class NetworkManager : public QObject {
    Q_OBJECT

    public:
      //void BroadcastGameState(const& World world);
      /**
       * @param server_address the address of the server to connect to
       * @param server_port port to connect to (UDP protocol)
       * @param client port port used in the client to receive data from the
       *        server (UDP protocol).
       */
      NetworkManager(QHostAddress server_address, quint16 server_port, quint16 client_port);

      /**
       * Starts communicating with the game server. This must be called after
       * the server has started the game, to start sending and receiving game
       * events.
       * If a game is already running, this will throw an exception.
       * @todo: actually throw the exception
       */
      void RunGame();

      /**
       * Ends the communication with the game server. Must be called once the
       * game is finished (to clean some resources). Must also be called before
       * the next call to RunGame.
       * Will throw an exception if the game was not running.
       * @todo: actually throw the exception
       */
      void StopGame();

      /**
       * Adds an event to the list of events to send to the server.
       * The event will then be repeatedly sent as long as the server does not
       * acknowledge it, so the user can use this method in a "fire and forget"
       * mode.
       * Once an event is added to the list, it can not be removed.
       */
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
