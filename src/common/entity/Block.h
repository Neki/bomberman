#ifndef SRC_COMMON_ENTITY_BLOCK_H_
#define SRC_COMMON_ENTITY_BLOCK_H_

#include <memory>
#include <QPoint>
#include "Entity.h"
#include "src/common/World.h"

namespace common {
namespace entity {

class Block : public Entity{

  public:
    Block(World* world, QPoint position);
    
    virtual void Update(int t);

    void HitByFire();
    /* Called when entity is hit by fire. */

  private:

};

}
}

#endif /* end of include guard: SRC_COMMON_ENTITY_BLOCK_H_ */

