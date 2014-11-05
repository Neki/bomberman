#ifndef SRC_COMMON_ENTITY_CHARACTER_H_
#define SRC_COMMON_ENTITY_CHARACTER_H_

#include <memory>
#include <QPoint>
#include "Entity.h"
#include <QPointF>

namespace common {
class GameEngine;
namespace entity {

class Character : public Entity {

  public:
    Character(QPoint position, int power = 1, float speed = 1.5f, unsigned int number_of_bombs = 1);

    unsigned int GetPower() const;
    QPointF GetCurrentSpeed() const;
    float GetSpeed() const;
    QPointF GetPositionF() const override; // in tile
    unsigned int GetNumberOfBombs() const;
    int GetBombDelay() const;

    virtual void Update(GameEngine* game_engine, int t);
    /* Method to be called at every frame.
	   t : duration of the frame in ms */

    void HitByFire(GameEngine* game_engine);
    /* Called when entity is hit by fire. */
    
    bool MoveTo(GameEngine* game_engine, QPoint target);

    bool operator==(const Character& other) const;

    void Serialize(QDataStream& stream) const override;

  private:
    float DistanceBetween(QPointF a, QPointF b);
  
    unsigned int power_; // bomb power in tiles
    QPointF current_speed_; // in tiles per second. might be temporary superior to the nominal speed
    float speed_; // nominal speed
    QPointF exact_position_;
    unsigned int number_of_bombs_;
  	int bomb_delay_;

    bool moving_;
    quint32 target_time_;
};

}
}

#endif /* end of include guard: SRC_COMMON_ENTITY_CHARACTER_H_ */

