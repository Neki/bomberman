#ifndef SRC_SERVER_NET_CLIENTEVENT_H_
#define SRC_SERVER_NET_CLIENTEVENT_H_

#include <qglobal.h>
#include "Client.h"

namespace net {

  /**
   * A container for an event received by the server.
   * T should be a subclass of common::net::Event, but there is no simple way in C++11 to
   * enforce that.
   * This is a templated version a BaseClientEvent that does not lose the event
   * exact type.
   */
  template<class T>
  class ClientEvent {

    public:
      ClientEvent(T event, Client client, quint32 server_timestamp)
        : event_(event),
          client_(client),
          server_timestamp_(server_timestamp) {
      }

      T getEventData() const {
        return event_;
      }

      quint8 getClientId() const {
        return client_.GetId();
      }

    private:
      T event_;
      Client client_;
      quint32 server_timestamp_;

  };

}

#endif
