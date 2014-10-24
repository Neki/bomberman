#ifndef SRC_SERVER_GAMEENGINE_H_
#define SRC_SERVER_GAMEENGINE_H_

#include <QPoint>
#include <QtCore>
#include <vector>
#include "src/common/net/Event.h"
#include "src/common/net/MoveEvent.h"
#include "src/common/net/BombEvent.h"
#include "src/common/net/MoveEvent.h"
//#include "src/common/net/InGameEventVisitor.h"
#include "World.h"
//#include "Strategy.h"
#include "Player.h"
#include "entity/Entity.h"
#include "entity/Fire.h"

namespace common {

class GameEngine : public InGameEventVisitor {

  public:
    GameEngine(std::vector<Player> players);

    void startGame();
    bool addEntity(std::unique_ptr<entity::Entity> e);
    World* GetWorld() const;
    
    void AddFireFromAtoB(QPoint a, QPoint b);
    
  private:
  
    QTime maxDuration;
    
    void update(int t); // t in ms. t is the duration of the frame
    
    void challengeStrategies();
    void simulate(int t); // t in ms. t is the duration of the frame
    void sendGameState();
    
    //void accept(BombEvent& e);
    //void accept(MoveEvent& e);
    
    void moveCharacter(int player_id, QPoint target);
    
    std::unique_ptr<World> world_;
    //std::unique_ptr<Strategy> strategies_;
    
};


}


#endif /* end of include guard: SRC_SERVER_GAMEENGINE_H_ */
