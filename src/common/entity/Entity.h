#ifndef SRC_COMMON_ENTITY_ENTITY_H_
#define SRC_COMMON_ENTITY_ENTITY_H_
#include <memory>
#include <QPoint>
#include <QString>
#include <QDataStream>
#include <QtSvg/QSvgRenderer>
#include <QCoreApplication>
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
    virtual std::shared_ptr<QSvgRenderer> GetSvgRenderer() = 0;

  protected:
    QPoint position_; // Entity position in the world's grid
    bool is_solid_;
    bool stops_fire_;
    bool should_be_removed_; // true if the entity should be removed by the game engine by the end of the frame
    QString texture_path_;

    bool operator==(const Entity& other) const;
    void SerializeBaseEntity(QDataStream& stream, EntityId entity_id) const;

  private:
    quint32 id_;
    quint16 temp_id_;

};

template<class T>
class DerivedEntity : public Entity {
public:
    DerivedEntity(QPoint position, bool is_solid, bool stops_fire, QString texture_path = "") :
        Entity(position, is_solid, stops_fire, texture_path) {}

    std::shared_ptr<QSvgRenderer> GetSvgRenderer() {
        if (!DerivedEntity::svg_renderer_) {
            DerivedEntity::svg_renderer_ = std::make_shared<QSvgRenderer>(QCoreApplication::applicationDirPath() + "/" + texture_path_);
        }

        return DerivedEntity::svg_renderer_;
    }

private:
    static std::shared_ptr<QSvgRenderer> svg_renderer_;
};

template<class T>
std::shared_ptr<QSvgRenderer> DerivedEntity<T>::svg_renderer_ = nullptr;

QDataStream& operator<<(QDataStream& stream, const Entity& entity);

}
}

#endif /* end of include guard: SRC_COMMON_ENTITY_ENTITY_H_ */

