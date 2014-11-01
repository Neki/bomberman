#include "gtest/gtest.h"
#include "src/common/entity/Character.h"
#include <QPoint>

TEST(Character, Character) {
  common::entity::Character c(QPoint(1,1), 1, 1.5f, 1);
  EXPECT_EQ(c.GetPower(), 1);
  EXPECT_EQ(c.GetPosition(), QPoint(1,1));
}
