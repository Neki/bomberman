#ifndef SRC_SERVER_NET_BASECLIENTEVENT_H_
#define SRC_SERVER_NET_BASECLIENTEVENT_H_

#include <memory>
#include "src/common/net/InGameEvent.h"
#include "Client.h"

using common::net::InGameEvent;

namespace net {

/*
 * A container for an event received by the server.
 */
class BaseClientEvent {
  public:
    BaseClientEvent(std::unique_ptr<InGameEvent> event, Client client, quint32 server_timestamp);
    Client GetClient() const;
    quint32 GetServerTimestamp() const;
    InGameEvent* GetEvent() const;

  private:
    std::unique_ptr<InGameEvent> event_;
    Client client_;
    quint32 server_timestamp_;
};

}

#endif


