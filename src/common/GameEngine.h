#ifndef SRC_SERVER_GAMEENGINE_H_
#define SRC_SERVER_GAMEENGINE_H_

#include <QObject>
#include <QPoint>
#include <QtCore>
#include "Event.h"
#include "MoveEvent.h"
#include "BombEvent.h"
#include "BombEvent.h"
#include "MoveEvent.h"
#include "World.h"
#include "Strategy.h"
#include "Player.h"

namespace common {


class GameEngine : public QObject {
  Q_OBJECT

  public:
    GameEngine();
    GameEngine(Vector<Player> players);

    void startGame();
    bool addEntity(Entity* entity);
    std::weak_ptr<World> GetWorld() const;
    
    void AddFireFromAtoB(QPoint a, QPoint b);
    
  private:
		
		void update(int t); // t in ms
  
    QTime maxDuration;
    
    void update(int t); // t in ms. t is the duration of the frame
    
    void challengeStrategies();
    void simulate(int t); // t in ms. t is the duration of the frame
    void sendGameState();
    
    bool accept(BombEvent& e);
    bool accept(MoveEvent& e);
    
    void moveCharacter(int player_id, QPoint target);
    
    std::shared_ptr<World> world_;
    std::unique_ptr<Strategy> strategies_;
    
};


}


#endif /* end of include guard: SRC_SERVER_GAMEENGINE_H_ */
