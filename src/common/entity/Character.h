#ifndef SRC_COMMON_ENTITY_CHARACTER_H_
#define SRC_COMMON_ENTITY_CHARACTER_H_

#include <memory>
#include <QPoint>
#include "Entity.h"
#include "src/common/World.h"

#include <QPointF>
#include <QTime>

namespace common {
namespace entity {

class Character : public Character {

  public:
    Character(std::weak_ptr<World> world, QPoint position);

    unsigned int GetPower() const;
    QPointF GetCurrentSpeed() const;
    float GetSpeed() const;
    QPointF GetExactPosition() const; // in tile
    unsigned int GetNumberOfBombs() const;
    QTime GetBombDelay() const;

    virtual void Update(unsigned int t) {};
    /* Method to be called at every frame.
	   t : duration of the frame in ms */

    void HitByFire();
    /* Called when entity is hit by fire. */

  private:
    unsigned int power_; // bomb power in tiles
    QPointF current_speed_; // in tiles per second. might be temporary superior to the nominal speed
    float speed_; // nominal speed
    QPointF exact_position_;
    unsigned int number_of_bombs_;
    
    void moveTo(QPoint t, int speed);
      
}

}
}

#endif /* end of include guard: SRC_COMMON_ENTITY_CHARACTER_H_ */

