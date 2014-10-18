#ifndef SRC_COMMON_ENTITY_BOMB_H_
#define SRC_COMMON_ENTITY_BOMB_H_

#include <memory>
#include <QPoint>
#include "Entity.h"
#include "src/common/World.h"
#include "Character.h"

#include <QTime>

namespace common {
namespace entity {

class Bomb : public Entity{

  public:
    Bomb(std::weak_ptr<World> world, QPoint position, std::weak_ptr<Character> bomber);

    std::weak_ptr<Character> GetBomber() const;
    QTime GetSetTime() const;
    QTime GetExplosionTime() const;

    virtual void HitByFire();
    /* Called when entity is hit by fire. */
	  
    virtual void Update(unsigned int t) {};
    /* Method to be called at every frame.
	   t : duration of the frame in ms */

  private:
    void explode();
  
    std::weak_ptr<Character> bomber_;
    QTime set_time_;
    QTime explosion_time_;
    unsigned int power_; // in tiles
}

}
}

#endif /* end of include guard: SRC_COMMON_ENTITY_BOMB_H_ */

