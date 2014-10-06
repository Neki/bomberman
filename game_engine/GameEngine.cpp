#include "World.h"
#include "GameEngine.h"
#include "Entity.h"
#include "Character.h"
#include "Bomb.h"
#include "Block.h"
#include "Wall.h"

#include <iostream>
#include <string>

using namespace std;

void GameEngine::startGame(void){
    world = new World();
}

void GameEngine::updateGame(void){
}

void GameEngine::validateActions(void){
}

void GameEngine::applyActions(void){
}

void GameEngine::simulateActions(void){
}

void GameEngine::sendGameState(void){
}

void GameEngine::moveCharacter(void){
}
