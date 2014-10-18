
#include "Entity.h"

namespace common {
namespace entity {

Entity::Entity(std::weak_ptr<World> world, QPoint position, bool is_solid) :
  world_(world),
  position_(position),
  is_solid_(is_solid),
  shouldBeRemoved_(false) {

}

QPoint Entity::GetPosition() const {
  return position_;
}

QPoint Entity::SetPosition(QPoint position) {
  position_ = position;
}

bool Entity::GetShouldBeRemoved() const {
  return shouldBeRemoved;
}

bool Entity::IsSolid () const {
  return is_solid_;
}

std::weak_ptr<World> Entity::GetWorld() const{
  return world_;
}

}
}
