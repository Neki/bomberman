#ifndef SRC_SERVER_WORLD_H_
#define SRC_SERVER_WORLD_H_

#include <memory>
#include <QPoint>
#include <vector>
#include "entity/Entity.h"
#include "entity/Character.h"

namespace common {

typedef std::vector<std::vector<std::vector<std::unique_ptr<entity::Entity> > > > grid_t;

class World {
  public:
    World(int width, int height);

    int GetWidth() const;
    int GetHeight() const;
    bool CheckCoord(QPoint p) const;
    bool IsWalkable(QPoint p) const; // Returns true if a character can walk on this case
    bool StopsFire(QPoint p) const; // Returns true if the case stops fire propagation
    bool AddItem(std::unique_ptr<entity::Entity> entity); // Adds an entity to the grid. Returns false if it fail.
    bool AddCharacter(std::unique_ptr<entity::Character> character); // Adds a character to characters_. Returns false if it fail.
    void removeEntities(); // Removes entities that should be removed

    entity::Character* GetCharacter(int id);

    std::vector<std::unique_ptr<entity::Entity> >::const_iterator IteratorAtBegin(QPoint a);
    std::vector<std::unique_ptr<entity::Entity> >::const_iterator IteratorAtEnd(QPoint a);
    std::vector<std::unique_ptr<entity::Character> >::const_iterator CharacterIteratorBegin();
    std::vector<std::unique_ptr<entity::Character> >::const_iterator CharacterIteratorEnd();
	bool IsEntitiesEmpty(QPoint a);

  private:
    const int width_; // Width of the world eg number of blocks
    const int height_;
    grid_t entities_;
    std::vector<std::unique_ptr<entity::Character> > characters_;
};

}

#endif