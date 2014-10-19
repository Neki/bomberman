#ifndef SRC_COMMON_ENTITY_FIRE_H_
#define SRC_COMMON_ENTITY_FIRE_H_

#include <memory>
#include <QPoint>
#include "Entity.h"
#include "src/common/World.h"

#include <QTime>

namespace common {
namespace entity {

class Fire : public Entity{

  public:
    Fire(std::weak_ptr<World> world, QPoint position);
    virtual ~Fire();

    QTime GetSetTime() const;
    QTime GetDisappearingTime() const;

    virtual void Update(int t);
    /* Method to be called at every frame.
	   t : duration of the frame in ms */

  private:
    QTime set_time_;
    QTime disappearing_time_;

};

}
}

#endif /* end of include guard: SRC_COMMON_ENTITY_FIRE_H_ */

