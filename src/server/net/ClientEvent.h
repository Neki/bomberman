#ifndef SRC_SERVER_NET_CLIENTEVENT_H_
#define SRC_SERVER_NET_CLIENTEVENT_H_

#include <qglobal.h>

namespace net {

  // T should be a subclass of common::net::Event, but there is no simple way in C++11 to
  // enforce that.
  // A wrapper around an event sent by a client, that includes additional
  // server-side information.
  template<class T>
  class ClientEvent {

    public:
      // TODO(faucon_b): Not sure about having to pass the event by copy
      ClientEvent(T event, quint8 client_id, quint64 server_timestamp);
      T getEventData() const;
      quint8 getClientId() const;

    private:
      T event_;
      quint64 server_timestamp_;
      quint8 client_id_;

  };

}

#endif
