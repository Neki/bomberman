#ifndef SRC_SERVER_WORLD_H_
#define SRC_SERVER_WORLD_H_

#include <vector>
#include "Entity.h"

namespace common {


  class World : public QObject {
    Q_OBJECT

    World(){ }

    private:
        QTime maxDuration;
        int wLength;
        int wHeight;
        std::vector<Entity::entity> myWorld;

        public:
        World(int length, int height, std::vector<Entity::entity> World);

        void setWorld(int length, int height, std::vector<Entity::entity> World);

        int GetLength() {return wLength;}
        int GetHeight() {return wHeight;}
        std::vector<Entity::entity> getEntityVector() {return myWorld;}

        bool IsEmpty(int x, int y);
        bool HasItem(int x, int y, Entity entity);
        void AddItem(int x, int y, Entity entity);
        void DestroyItem(int x, int y, Entity entity);
  };


}


#endif
