
#include "Entity.h"

namespace common {
namespace entity {

Entity::Entity(std::weak_ptr<World> world, QPoint position, bool is_solid, bool stops_fire, QString texture_path)
  : is_solid_(is_solid),
    stops_fire_(stops_fire),
    should_be_removed_(false),
    world_(world),
    position_(position),
    texture_path_(texture_path) {

}

void Entity::Update(int t)
{
  (void) t;
}

void Entity::IsWalkedOn(std::weak_ptr<GameEngine> game_engine, const std::weak_ptr<Character> character)
{
  (void) game_engine;
  (void) character;
}

QPoint Entity::GetPosition() const {
  return position_;
}

void Entity::SetPosition(QPoint position) {
  position_ = position;
}

bool Entity::GetShouldBeRemoved() const {
  return should_be_removed_;
}

bool Entity::IsSolid () const {
  return is_solid_;
}

bool Entity::StopsFire () const {
  return stops_fire_;
}

QString Entity::GetTexturePath() const {
  return texture_path_;
}

std::weak_ptr<World> Entity::GetWorld() const{
  return world_;
}

}
}
