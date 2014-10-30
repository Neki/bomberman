#ifndef SRC_COMMON_ENTITY_FIRE_H_
#define SRC_COMMON_ENTITY_FIRE_H_

#include <memory>
#include <QPoint>
#include "Entity.h"
#include "src/common/GameEngine.h"

#include <QTime>

namespace common {
namespace entity {

class Fire : public Entity{

  public:
    Fire(QPoint position, quint32 set_time);

    quint32 GetSetTime() const;
    quint32 GetDisappearingTime() const;

    virtual void Update(std::weak_ptr<GameEngine> game_engine, int t);
    /* Method to be called at every frame.
	   t : duration of the frame in ms */

    bool operator==(const Fire& other) const;

    void Serialize(QDataStream& stream) const override;

  private:
    quint32 set_time_;
    quint32 disappearing_time_;

};

}
}

#endif /* end of include guard: SRC_COMMON_ENTITY_FIRE_H_ */

