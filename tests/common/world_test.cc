#include "gtest/gtest.h"
#include "src/common/World.h"
#include "src/common/entity/Wall.h"
#include <QPoint>

TEST(World, World) {
  common::World world(30,10);
  EXPECT_EQ(world.GetWidth(), 30);
  EXPECT_EQ(world.GetHeight(), 10);
}

TEST(World, CheckCoord) {
  common::World world(30,10);
  EXPECT_EQ(world.CheckCoord(QPoint(0, 0)), true);
  EXPECT_EQ(world.CheckCoord(QPoint(29, 9)), true);
  EXPECT_EQ(world.CheckCoord(QPoint(0, 9)), true);
  EXPECT_EQ(world.CheckCoord(QPoint(29, 0)), true);
  EXPECT_EQ(world.CheckCoord(QPoint(5, 6)), true);
  EXPECT_EQ(world.CheckCoord(QPoint(-1, -1)), false);
  EXPECT_EQ(world.CheckCoord(QPoint(-1, 0)), false);
  EXPECT_EQ(world.CheckCoord(QPoint(30, 2)), false);
  EXPECT_EQ(world.CheckCoord(QPoint(14, 10)), false);
}

TEST(World, AddItem) {
  common::World world(30,10);
  QPoint pos(4, 4);
  world.AddItem(std::unique_ptr<common::entity::Wall>( new common::entity::Wall(pos)));
  EXPECT_EQ(world.IsWalkable(pos), false);
  EXPECT_EQ(world.StopsFire(pos), true);
  EXPECT_EQ(world.IsWalkable(QPoint(3, 3)), true);
  EXPECT_EQ(world.StopsFire(QPoint(3, 3)), false);
}
