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

    virtual void Update(GameEngine* game_engine, int t);

    void HitByFire(GameEngine* game_engine);
    /* Called when entity is hit by fire. */

    bool operator==(const Bonus& other) const;

    void Serialize(QDataStream& stream) const override;

  private:

};

}
}

#endif /* end of include guard: SRC_COMMON_ENTITY_BONUS_H_ */

