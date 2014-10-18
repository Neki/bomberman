#ifndef SRC_COMMON_ENTITY_BONUS_H_
#define SRC_COMMON_ENTITY_BONUS_H_

#include <memory>
#include <QPoint>
#include "Entity.h"
#include "src/common/World.h"

namespace common {
namespace entity {

  class Bonus : public Entity {

    public:
      Bonus(std::weak_ptr<World> world, QPoint position);
      
      void HitByFire();
      /* Called when entity is hit by fire. */

    private:

  }

}
}

#endif /* end of include guard: SRC_COMMON_ENTITY_BONUS_H_ */

