#ifndef SRC_COMMON_ENTITY_WALL_H_
#define SRC_COMMON_ENTITY_WALL_H_

#include <memory>
#include <QPoint>
#include "Entity.h"
#include "src/common/GameEngine.h"

namespace common {
namespace entity {

class Wall : public Entity{

  public:
    Wall(QPoint position);
    virtual void Update(std::weak_ptr<GameEngine> game_engine, int t);

    bool operator==(const Wall& other);

    void Serialize(QDataStream& stream) const override;

  private:

};

}
}

#endif /* end of include guard: SRC_COMMON_ENTITY_WALL_H_ */

