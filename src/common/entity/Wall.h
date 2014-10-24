#ifndef SRC_COMMON_ENTITY_WALL_H_
#define SRC_COMMON_ENTITY_WALL_H_

#include <memory>
#include <QPoint>
#include "Entity.h"
#include "src/common/World.h"

namespace common {
namespace entity {

class Wall : public Entity{

  public:
    Wall(World* world, QPoint position);
    virtual void Update(int t);

  private:

};

}
}

#endif /* end of include guard: SRC_COMMON_ENTITY_WALL_H_ */

