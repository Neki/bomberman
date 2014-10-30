#include "ServerEntity.h"

namespace net {

ServerEntity::ServerEntity(quint32 timestamp, std::unique_ptr<Entity> entity)
  : timestamp_(timestamp),
    entity_(std::move(entity)) {}

quint32 ServerEntity::GetTimestamp() {
  return timestamp_;
}

Entity* ServerEntity::GetEntity() {
  return entity_.get();
}


}
