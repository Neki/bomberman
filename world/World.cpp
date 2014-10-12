#include "World.h"
#include "Entity.h"

#include <iostream>
#include <vector>

World::World(int width, int height) :
    width_(width),
    height_(height),
    entities_(nullptr)
{
    entities_ = new std::vector<std::vector<std::vector<entity::Entity*>>>(width_);
}

World::~World() {
    // TODO libérer la mémoire
}

int World::GetWidth(){
    return width_;
}

int World::GetHeight(){
    return height_;
}

bool World::CheckCoord(int x, int y){
    if(x<0 || x >= width_ || y<0 || y >= height_)
        {
            return false;
        }
    else
        return true;
}

bool World::IsWalkable(int x, int y)
{
    if(!CheckCoord(x,y))
        return false;

    for(auto entity: entities_[x][y]){
        if(entity -> IsSolid()){
            return false;
        }
    }
    return true;
}

void World::AddItem(int x, int y, Entity* entity){
    if(!checkCoord(x,y)){
        // TODO exception
        return;
    }
    World[x][y].insert(entity);
}

void World::RemoveItem(int id){
    for(auto columns: entities_){
        for(auto blocks: columns){
            for(auto i = blocks.begin(); blocks.end();){
                if(i -> getId() == id){
                   i = blocks.erase(i);
                }else{
                    ++i;
                }
            }
        }
    }
}



