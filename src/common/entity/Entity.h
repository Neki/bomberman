#ifndef SRC_COMMON_ENTITY_ENTITY_H_
#define SRC_COMMON_ENTITY_ENTITY_H_

#include <memory>
#include <QPoint>
#include <QString>
#include "src/common/World.h"
#include "src/common/GameEngine.h

namespace common {
namespace entity {

class Character;

class Entity {

  public:
    Entity(std::weak_ptr<World> world, QPoint position, bool is_solid, bool stops_fire, QString texture_path = "");
    virtual ~Entity();

    virtual void Update(int t) = 0;
    /* Method called at every frame.
	   t : duration of the frame in ms */

    virtual void HitByFire() {};
    /* Called when entity is hit by fire */

    virtual bool IsSolid() const;
    /* Returns true if entity can not be walked through. Returns false otherwise. */
    
    virtual bool StopsFire() const;
    /* Returns true if entity stops fire propagation. Returns false otherwise. */
	
    virtual void IsWalkedOn(std::weak_ptr<GameEngine> game_engine, const std::weak_ptr<Character> character);
    /* Called when a character walk on the entity */

    QPoint GetPosition() const;
    void SetPosition(QPoint position);
    bool GetShouldBeRemoved() const;
    QString GetTexturePath() const;
	
  protected:
    std::weak_ptr<World> GetWorld() const;
    bool is_solid_;
    bool stops_fire_;
    bool should_be_removed_; // true if the entity should be removed by the game engine by the end of the frame

  private:
	std::weak_ptr<World> world_;
	QPoint position_; // Entity position in the world's grid
  QString texture_path_;
};

}
}

#endif /* end of include guard: SRC_COMMON_ENTITY_ENTITY_H_ */

