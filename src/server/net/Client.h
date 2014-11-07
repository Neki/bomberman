#ifndef SRC_SERVER_NET_CLIENT_H_
#define SRC_SERVER_NET_CLIENT_H_

#include <QHostAddress>

namespace net {

/**
 * Represents a client that was connected (at some point) to the game.
 * Each client has an ID (8 bits unsigned). Instantiators of this class
 * shloud ensure they use unique IDs for all the clients.
 * If the client is disconnected, you can use the SetConnected() method to
 * mark the client as disconnected.
 */
class Client {

  public:
    Client(int client_id, QHostAddress address, quint16 port_, bool is_connected = true);
    int GetId() const;
    quint16 GetPort() const;
    QHostAddress GetAddress() const;
    bool IsConnected() const;
    void SetConnected(bool is_connected);

  private:
    int id_;
    QHostAddress address_;
    quint16 port_;
    bool is_connected_;

};

}

#endif

