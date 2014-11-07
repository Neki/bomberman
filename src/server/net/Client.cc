#include "Client.h"

namespace net {

Client::Client(int client_id, QHostAddress address, quint16 port, bool is_connected)
  : id_(client_id),
    address_(address),
    port_(port),
    is_connected_(is_connected) {

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

bool Client::IsConnected() const {
  return is_connected_;
}

void Client::SetConnected(bool is_connected) {
  is_connected_ = is_connected;
}

}

