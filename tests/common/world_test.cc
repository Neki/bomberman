#include "gtest/gtest.h"
#include "src/common/World.h"
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
