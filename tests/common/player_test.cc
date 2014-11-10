#include "gtest/gtest.h"
#include "src/common/Player.h"

TEST(Player, SubstractScore) {
    common::Player player(1, "SpiderMan");
    player.SubstractScore(3);
    EXPECT_EQ(player.GetScore(), -3);
}