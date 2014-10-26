
#include "Entity.h"

namespace common {
namespace entity {

Entity::Entity(QPoint position, bool is_solid, bool stops_fire, QString texture_path)
  : position_(position), 
    is_solid_(is_solid),
    stops_fire_(stops_fire),
    should_be_removed_(false),
    texture_path_(texture_path),
    id_(0) {

}

Entity::~Entity() {

}

void Entity::Update(std::weak_ptr<GameEngine> game_engine, int t)
{
  (void) game_engine;
  (void) t;
}

void Entity::HitByFire(std::weak_ptr<GameEngine> game_engine) {
  (void) game_engine;
}

void Entity::IsWalkedOn(std::weak_ptr<GameEngine> game_engine, const std::weak_ptr<Character> character)
{
  (void) game_engine;
  (void) character;
}

QPoint Entity::GetPosition() const {
  return position_;
}

QPointF Entity::GetPositionF() const {
  return QPointF(position_);
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

int Entity::GetId() const {
  return id_;
}

}
}
