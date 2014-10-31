#ifndef SRC_CLIENT_NET_SERVERENTITY_H_
#define SRC_CLIENT_NET_SERVERENTITY_H_

#include <qobject.h>
#include <memory>
#include "src/common/entity/Entity.h"

using common::entity::Entity;

namespace net {

class ServerEntity {
  public:
    ServerEntity(quint32 timestamp, std::unique_ptr<Entity> entity);

    quint32 GetTimestamp();
    Entity* GetEntity();

  private:
    quint32 timestamp_;
    std::unique_ptr<Entity> entity_;

};

}


#endif

