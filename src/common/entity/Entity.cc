
#include "Entity.h"

namespace common {
namespace entity {

Entity::Entity(std::weak_ptr<World> world, QPoint position, bool is_solid, bool stops_fire) :
  world_(world),
  position_(position),
  is_solid_(is_solid),
  stops_fire_(stops_fire),
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

bool Entity::StopsFire () const {
  return stops_fire_;
}

std::weak_ptr<World> Entity::GetWorld() const{
  return world_;
}

}
}
