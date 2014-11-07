#ifndef SRC_COMMON_ENTITY_ENTITY_H_
#define SRC_COMMON_ENTITY_ENTITY_H_

#include <memory>
#include <QPoint>
#include <QDataStream>
#include "src/common/GameEngine.h"
#include "EntityId.h"

namespace common {
namespace entity {

class Character;

class Entity {

  public:
    Entity(QPoint position, bool is_solid, bool stops_fire, QString texture_path = "");
    virtual ~Entity();

    virtual void Update(std::weak_ptr<GameEngine> game_engine, int t) = 0;
    /* Method called at every frame.
	   t : duration of the frame in ms */

    virtual void HitByFire(std::weak_ptr<GameEngine> game_engine);
    /* Called when entity is hit by fire */

    virtual bool IsSolid() const;
    /* Returns true if entity can not be walked through. Returns false otherwise. */

    virtual bool StopsFire() const;
    /* Returns true if entity stops fire propagation. Returns false otherwise. */

    virtual void IsWalkedOn(std::weak_ptr<GameEngine> game_engine, const std::weak_ptr<Character> character);
    /* Called when a character walk on the entity */

    virtual QPoint GetPosition() const;
    virtual QPointF GetPositionF() const;
    bool GetShouldBeRemoved() const;
    virtual QString GetTexturePath() const;
    int GetId() const;

    virtual void Serialize(QDataStream& stream) const = 0;


  protected:
    QPoint position_; // Entity position in the world's grid
    QString texture_path_;
    bool is_solid_;
    bool stops_fire_;
    bool should_be_removed_; // true if the entity should be removed by the game engine by the end of the frame

    bool operator==(const Entity& other) const;
    void SerializeBaseEntity(QDataStream& stream, EntityId entity_id) const;

  private:
    quint32 id_;
    quint16 temp_id_;
};


QDataStream& operator<<(QDataStream& stream, const Entity& entity);

}
}

#endif /* end of include guard: SRC_COMMON_ENTITY_ENTITY_H_ */

