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

TEST(World, Check_map_generation) {
  common::World world(21, 11);

  EXPECT_EQ(world.IsWalkable(QPoint(0, 0)), true);
  EXPECT_EQ(world.IsWalkable(QPoint(1, 0)), true);
  EXPECT_EQ(world.IsWalkable(QPoint(0, 1)), true);
  EXPECT_EQ(world.IsWalkable(QPoint(20, 10)), true);
  EXPECT_EQ(world.IsWalkable(QPoint(19, 10)), true);
  EXPECT_EQ(world.IsWalkable(QPoint(20, 9)), true);
  EXPECT_EQ(world.IsWalkable(QPoint(0, 10)), true);
  EXPECT_EQ(world.IsWalkable(QPoint(0, 9)), true);
  EXPECT_EQ(world.IsWalkable(QPoint(1, 10)), true);
  EXPECT_EQ(world.IsWalkable(QPoint(20, 0)), true);
  EXPECT_EQ(world.IsWalkable(QPoint(20, 1)), true);
  EXPECT_EQ(world.IsWalkable(QPoint(19, 0)), true);

  EXPECT_EQ(world.IsWalkable(QPoint(-1, 0)), false);
  EXPECT_EQ(world.IsWalkable(QPoint(1, 1)), false);
  EXPECT_EQ(world.IsWalkable(QPoint(2, 1)), false);
  EXPECT_EQ(world.IsWalkable(QPoint(1, 2)), false);
  EXPECT_EQ(world.IsWalkable(QPoint(0, 6)), false);
  EXPECT_EQ(world.IsWalkable(QPoint(10, 0)), false);
  EXPECT_EQ(world.IsWalkable(QPoint(10, 1)), false);
  EXPECT_EQ(world.IsWalkable(QPoint(21, 11)), false);
  EXPECT_EQ(world.IsWalkable(QPoint(6, 6)), false);
  EXPECT_EQ(world.IsWalkable(QPoint(20, 11)), false);
  EXPECT_EQ(world.IsWalkable(QPoint(2, 10)), false);
  EXPECT_EQ(world.IsWalkable(QPoint(20, 2)), false);

}
