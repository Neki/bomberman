#ifndef SRC_SERVER_WORLD_H_
#define SRC_SERVER_WORLD_H_

#include <QtCore>
#include "Entity.h"


namespace common {


  class World : public QObject {
    Q_OBJECT

    World(){ }

    private:
		QTime maxDuration;
        int p_length;
        int p_height;
        std::Vector<Entity::entity> p_world[length][height];

        public:
        World(int length, int height, std::Vector<Entity::entity> world[length][height]);

        void setWorld(int length, int height, std::Vector<Entity::entity> world[length][height]);

        int getLength() {return p_length;}
        int getHeight() {return p_height;}
        std::Vector<Entity::entity> getEntityVector() {return p_world[length][height];}

        bool isEmpty(int x, int y);
        bool hasItem(int x, int y);
        void addItem(int x, int y);
        void destroyItem(int x, int y);

  };


}


#endif /* end of include guard: SRC_SERVER_WORLD_H_ */
