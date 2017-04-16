#ifndef SRC_SERVER_WORLD_H_
#define SRC_SERVER_WORLD_H_

#include <vector>
#include "Entity.h"
#include "Character.h"

namespace common {


  class World {
    World(){ }

    private:
        int width_; // Width of the world eg number of blocks
        int height_;
        std::vector<std::vector<std::vector<Entity::Entity*>>>* entities_;
        std::vector<Character::Character> characters_;

    public:
        World(int width, int height);
        ~World();

        bool CheckCoord(int x, int y);

        int GetWidth();
        int GetHeight();

        bool IsWalkable(int x, int y);
        void AddItem(int x, int y, Entity* entity);
        void RemoveItem(int id);
  };
}


#endif
