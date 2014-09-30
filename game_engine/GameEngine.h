#ifndef SRC_SERVER_GAMEENGINE_H_
#define SRC_SERVER_GAMEENGINE_H_

#include <QtCore>
#include "Event.h"
#include "MoveEvent.h"
#include "BombEvent.h"

namespace common {


  class GameEngine : public QObject {
    Q_OBJECT

    public:
		GameEngine(Vector<Player> players, QTime maxDuration, QTime suddenDeathModeDuration);
        int start();
        int move();
        // For fire, bomb, bonus, bloc, wall
        bool isEmpty(int x, int y);
        bool hasItem(int x, int y);
        void addItem(int x, int y);
        void destroyItem(int x, int y);

    private:
		QTime maxDuration;
		Characters;
		Players;
		
		void update(int t); // t in ms

  };


}


#endif /* end of include guard: SRC_SERVER_GAMEENGINE_H_ */
