#ifndef SRC_COMMON_ENTITY_ENTITY_H_
#define SRC_COMMON_ENTITY_ENTITY_H_

#include <memory>
#include <QPoint>
#include <QString>
#include "src/common/World.h"
#include "Character.h"

namespace common {
namespace entity {

class Entity {

  public:
    Entity(std::weak_ptr<World> world, QPoint position, bool is_solid, bool stops_fire, QString texture_path = "");
	
    virtual void Update(unsigned int t) {};
    /* Method called at every frame.
	   t : duration of the frame in ms */

    virtual void HitByFire() {};
    /* Called when entity is hit by fire */

    virtual bool IsSolid();
    /* Returns true if entity can not be walked through. Returns false otherwise. */
    
    virtual bool StopsFire();
    /* Returns true if entity stops fire propagation. Returns false otherwise. */
	
    virtual void IsWalkedOn(GameEngine* gameEngine, Character* character const) {};
    /* Called when a character walk on the entity */

    QPoint GetPosition() const;
    QPoint SetPosition(QPoint position);
    bool GetShouldBeRemoved() const;
    QString GetTexturePath() const;
	
  protected:
    std::weak_ptr<World> GetWorld() const;
    bool is_solid_;
    bool stops_fire_;
    bool should_be_removed_; // true if the entity should be removed by the game engine by the end of the frame

  private:
    ~Entity() {};
    QPoint position_; // Entity position in the world's grid
    std::weak_ptr<World> world_;
    QString texture_path_;
}

}
}

#endif /* end of include guard: SRC_COMMON_ENTITY_ENTITY_H_ */

