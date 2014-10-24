#ifndef SRC_SERVER_NET_CLIENT_H_
#define SRC_SERVER_NET_CLIENT_H_

#include <QHostAddress>

namespace net {

/**
 * Represents a client connected to the game.
 */
class Client {

  public:
    Client(int client_id, QHostAddress address, quint16 port_);
    int GetId() const;
    quint16 GetPort() const;
    QHostAddress GetAddress() const;

  private:
    int id_;
    QHostAddress address_;
    quint16 port_;

};

}

#endif

