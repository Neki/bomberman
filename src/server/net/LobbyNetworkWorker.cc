#include "LobbyNetworkWorker.h"
#include "easylogging++.h"

#include <cassert>
#include <QTcpSocket>

namespace net {

LobbyNetworkWorker::LobbyNetworkWorker(quint16 server_port, int max_clients)
  : server_port_(server_port),
    max_clients_(max_clients),
    tcp_server_(this) {
  connect(&tcp_server_, &QTcpServer::newConnection, this, &LobbyNetworkWorker::AcceptNewClient);
  // todo : check the return value of listen()
  tcp_server_.listen(QHostAddress::Any, server_port_);
}

void LobbyNetworkWorker::AcceptNewClient() {
  while(tcp_server_.hasPendingConnections()) {
    // according to the Qt docs, the created socket will be destroyed when the
    // TCP server is destroyed
    // but we do not rely on it to make things explicit
    std::unique_ptr<QTcpSocket> socket(tcp_server_.nextPendingConnection());
    Client client = CreateNewClient(std::move(socket));
  }
}

Client LobbyNetworkWorker::CreateNewClient(std::unique_ptr<QTcpSocket> socket) {
  Client client(0, QHostAddress("127.0.0.1"), 4567, true);
  connect(socket.get(), &QTcpSocket::readyRead, [this, client] () {
    ProcessClientData(client);
  });
  connected_clients_.insert(std::pair<Client, std::unique_ptr<QTcpSocket>>(client, std::move(socket)));
  return client;
}

void LobbyNetworkWorker::ProcessClientData(Client client) {
  auto it = connected_clients_.find(client);
  assert(it != connected_clients_.end());
 //  auto& socket = it->second;
}

}
