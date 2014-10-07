#include "ClientEvent.h"

namespace net {

template<class T>
ClientEvent<T>::ClientEvent(T event, quint8 client_id, quint64 server_timestamp)
    : event_(event),
      client_id_(client_id),
      server_timestamp_(server_timestamp) {

}

template<class T>
T ClientEvent<T>::getEventData() const {
  return event_;
}

template<class T>
quint8 ClientEvent<T>::getClientId() const {
  return client_id_;
}

}
