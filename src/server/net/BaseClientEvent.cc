#include "BaseClientEvent.h"

namespace net {

BaseClientEvent::BaseClientEvent(std::unique_ptr<InGameEvent> event, Client client, quint32 server_timestamp)
  : event_(std::move(event)),
    client_(client),
    server_timestamp_(server_timestamp) {

}

Client BaseClientEvent::GetClient() const {
  return client_;
}

quint32 BaseClientEvent::GetServerTimestamp() const {
  return server_timestamp_;
}

InGameEvent* BaseClientEvent::GetEvent() const {
  return event_.get();
}

}
