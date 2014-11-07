#ifndef SRC_COMMON_ENTITY_CHARACTER_H_
#define SRC_COMMON_ENTITY_CHARACTER_H_

#include <memory>
#include <QPoint>
#include "Entity.h"
#include "src/common/GameEngine.h"

#include <QPointF>
#include <QTime>

namespace common {
namespace entity {

class Character : public Entity {

  public:
    Character(QPoint position, int power = 1, float speed = 1.5f, unsigned int number_of_bombs = 1);

    unsigned int GetPower() const;
    QPointF GetCurrentSpeed() const;
    float GetSpeed() const;
    QPointF GetPositionF() const; // in tile
    unsigned int GetNumberOfBombs() const;
    int GetBombDelay() const;

    virtual void Update(std::weak_ptr<GameEngine> game_engine, int t);
    /* Method to be called at every frame.
	   t : duration of the frame in ms */

    void HitByFire(std::weak_ptr<GameEngine> game_engine);
    /* Called when entity is hit by fire. */

    bool operator==(const Character& other) const;

    void Serialize(QDataStream& stream) const override;

  private:
    unsigned int power_; // bomb power in tiles
    QPointF current_speed_; // in tiles per second. might be temporary superior to the nominal speed
    float speed_; // nominal speed
    QPointF exact_position_;
    unsigned int number_of_bombs_;
  	int bomb_delay_;

    void moveTo(QPoint t, int speed);

};

}
}

#endif /* end of include guard: SRC_COMMON_ENTITY_CHARACTER_H_ */

