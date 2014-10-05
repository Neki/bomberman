#include "World.h"
#include "Entity.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;


// World constructor
World::World(int length, int height, std::vector<Entity::entity> world)
{
   SetWorld(length, height, World[length][height]);
}

void World::World(int length, int height, std::vector<Entity::entity> world)
{
    wLength = length;
    wHeight = height;
    world = world;
}

void CheckCoord(int x, int y){
    if(x<0 || x > length || y<0 || y > height)
        {
            throw CoordOutOfRange;
        }
}

bool IsEmpty(int x, int y)
{
    CheckCoord(x,y);
    if(world[x][y].size() > 0){
        return false;
    }else{
        return true;
    }
}

bool HasItem(int x, int y, Entity entity)
{
    checkCoord(x,y);
    for(int i=0; i<World[x][y].size();i++ ){
        if(World[x][y].at(i) == entity){
            return True;
        }
    }
    returne False;
}


void AddItem(int x, int y, Entity entity){
    checkCoord(x,y);
    World[x][y].insert(entity);
}

void DestroyItem(int x, int y, Entity entity){
    checkCoord(x,y);
    for(int i=0; i<World[x][y].size();i++ ){
        if(World[x][y].at(i) == entity){
            World[x][y].erase(i);
        }
    }
}
