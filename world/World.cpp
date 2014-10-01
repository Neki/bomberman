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
    SetWorld(length, height, world[length][height]);
}

void World::World(int length, int height, std::Vector<Entity::entity> world[length][height])
{
    p_length = length;
    p_height = heigth;
    p_world = world;
}
