#ifndef SRC_SERVER_NET_LOBBYNETWORKWORKER_H_
#define SRC_SERVER_NET_LOBBYNETWORKWORKER_H_

#include <memory>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "Client.h"

namespace net {

class LobbyNetworkWorker : public QObject {
  Q_OBJECT

  public:
    LobbyNetworkWorker(quint16 server_port, int max_clients);

  signals:
    void NewClientConnected(Client client, QString player_name);
    void ClientDisconnected(Client client);

  private slots:
    void AcceptNewClient();

  private:
    int max_clients_;
    quint16 server_port_;
    QTcpServer tcp_server_;
    std::map<Client, std::unique_ptr<QTcpSocket>> connected_clients_; // FIXME: implement operator< for Client ?

    Client CreateNewClient(std::unique_ptr<QTcpSocket> socket);
    void ProcessClientData(Client client);


};

}

#endif

