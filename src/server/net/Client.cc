#include "Client.h"

namespace net {

Client::Client(int client_id, QHostAddress address, quint16 port)
  : id_(client_id),
    address_(address),
    port_(port) {

}

int Client::GetId() const {
  return id_;
}

QHostAddress Client::GetAddress() const {
  return address_;
}

quint16 Client::GetPort() const {
  return port_;
}

}

