#ifndef SRC_COMMON_ENTITY_BONUS_H_
#define SRC_COMMON_ENTITY_BONUS_H_

#include <QString>
#include "Entity.h"
#include "src/common/GameEngine.h"

namespace common {
namespace entity {

class Bonus : public Entity {

  public:
    Bonus(QPoint position, QString texture_path = "");
    
    virtual void Update(std::weak_ptr<GameEngine> game_engine, int t);
    
    void HitByFire(std::weak_ptr<GameEngine> game_engine);
    /* Called when entity is hit by fire. */

  private:

};

}
}

#endif /* end of include guard: SRC_COMMON_ENTITY_BONUS_H_ */

