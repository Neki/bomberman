#ifndef SRC_COMMON_ENTITY_BLOCK_H_
#define SRC_COMMON_ENTITY_BLOCK_H_

#include <memory>
#include <QPoint>
#include "Entity.h"
#include "src/common/GameEngine.h"

namespace common {
namespace entity {

class Block : public DerivedEntity<Block> {

  public:
    Block(QPoint position);

    virtual void Update(std::weak_ptr<GameEngine> game_engine, int t);

    void HitByFire(std::weak_ptr<GameEngine> game_engine);
    /* Called when entity is hit by fire. */

    bool operator==(const Block& other) const;

    void Serialize(QDataStream& stream) const override;

  private:

};

}
}

#endif /* end of include guard: SRC_COMMON_ENTITY_BLOCK_H_ */

