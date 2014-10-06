#ifndef SRC_SERVER_GAMEENGINE_H_
#define SRC_SERVER_GAMEENGINE_H_

#include <QtCore>
#include "Event.h"
#include "MoveEvent.h"
#include "BombEvent.h"
#include "World.h"

namespace common {


  class GameEngine : public QObject {
    Q_OBJECT

    public:
		GameEngine(Vector<Player> players, QTime maxDuration, QTime suddenDeathModeDuration);
        void startGame();
        void updateGame();
        void validateActions();
        void applyActions();
        void simulateActions();
        void sendGameState();
        void moveCharacter();

    private:
		QTime maxDuration;
		Characters;
		Players;
        World world;
		
		void update(int t); // t in ms

  };


}


#endif /* end of include guard: SRC_SERVER_GAMEENGINE_H_ */
