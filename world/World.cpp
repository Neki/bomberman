#include "World.h"
#include "Entity.h"
#include "Character.h"
#include "Bomb.h"
#include "Block.h"
#include "Wall.h"

#include <iostream>
#include <string>

using namespace std;


// World constructor
World::World(int length, int height, std::Vector<Entity::entity> world[length][height])
{
   setWorld(length, height, world[length][height]);
}

void World::World(int length, int height, std::Vector<Entity::entity> world[length][height])
{
    p_length = length;
    p_height = heigth;
    p_world = world;
}

void checkCoord(int x, int y){
    if(x<0 || x > length || y<0 || y > heigth)
        {
            throw CoordOutOfRange;
        }
}

bool isEmpty(int x, int y)
{
    checkCoord(x,y);
    if(World[x][y].size() > 0){
        return False;
    }else{
        return True;
    }
}

bool hasItem(int x, int y, Entity entity)
{
    checkCoord(x,y);
    for(int i=0; i<World[x][y].size();i++ ){
        if(World[x][y].at(i) == entity){
            return True;
        }
    }
    returne False;
}


void addItem(int x, int y, Entity entity){
    checkCoord(x,y);
    World[x][y].insert(entity);
}

void destroyItem(int x, int y, Entity entity){
    checkCoord(x,y);
    for(int i=0; i<World[x][y].size();i++ ){
        if(World[x][y].at(i) == entity){
            World[x][y].erase(i);
        }
    }
}
