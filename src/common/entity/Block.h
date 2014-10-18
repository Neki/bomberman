#ifndef SRC_COMMON_ENTITY_BLOCK_H_
#define SRC_COMMON_ENTITY_BLOCK_H_

#include <memory>
#include <QPoint>
#include "Entity.h"
#include "World.h"

namespace common {
namespace entity {

class Block : public Entity{

  public:
    Block(std::weak_ptr<World> world, QPoint position);

    void HitByFire();
    /* Called when entity is hit by fire. */

  private:

}

}
}

#endif /* end of include guard: SRC_COMMON_ENTITY_BLOCK_H_

