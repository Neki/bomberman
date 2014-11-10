#include "src/common/GameEngine.h"
#include "Entity.h"

namespace common {
namespace entity {

Entity::Entity(QPoint position, bool is_solid, bool stops_fire, QString texture_path)
  : position_(position),
    texture_path_(texture_path),
    is_solid_(is_solid),
    stops_fire_(stops_fire),
    should_be_removed_(false),
    id_(0),
    temp_id_(0) { // TODO generate an actual temp id

}

Entity::~Entity() {

}

void Entity::Update(GameEngine* game_engine, int t)
{
  (void) game_engine;
  (void) t;
}

void Entity::HitByFire(GameEngine* game_engine) {
  (void) game_engine;
}

void Entity::IsWalkedOn(GameEngine* game_engine, const std::weak_ptr<Character> character)
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

void Entity::SerializeBaseEntity(QDataStream& stream, EntityId entity_id) const {
  stream << (quint8) entity_id;
  stream << id_;
  stream << temp_id_;
  stream << position_;
}

bool Entity::operator==(const Entity& other) const {
  //FIXME : once the id will be properly handled, make the correct comparison
  return is_solid_ == other.is_solid_ && stops_fire_ == other.stops_fire_ && position_ == other.position_;
}

QDataStream& operator<<(QDataStream& stream, const Entity& entity) {
  entity.Serialize(stream);
  return stream;
}

}
}
