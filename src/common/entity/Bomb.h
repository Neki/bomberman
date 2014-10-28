#ifndef SRC_COMMON_ENTITY_BOMB_H_
#define SRC_COMMON_ENTITY_BOMB_H_

#include <memory>
#include <QPoint>
#include <QTime>

#include "Entity.h"
#include "src/common/GameEngine.h"
#include "Character.h"

namespace common {
namespace entity {

class Bomb : public Entity{

  public:

    Bomb(QPoint position, quint32 set_time, quint32 explosion_time, int power);

    std::weak_ptr<Character> GetBomber() const;
    quint32 GetSetTime() const;
    quint32 GetExplosionTime() const;

    virtual void HitByFire(std::weak_ptr<GameEngine> game_engine);
    /* Called when entity is hit by fire. */

    virtual void Update(std::weak_ptr<GameEngine> game_engine, int t);
    /* Method to be called at every frame.
	   t : duration of the frame in ms */

    void Serialize(QDataStream& stream) const override;

  private:
    void explode(std::weak_ptr<GameEngine> game_engine);

    quint32 set_time_;
    quint32 explosion_time_;
    int power_; // in tiles
};

}
}

#endif /* end of include guard: SRC_COMMON_ENTITY_BOMB_H_ */

