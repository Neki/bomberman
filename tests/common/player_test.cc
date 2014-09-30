#include "gtest/gtest.h"
#include "../../src/common/Player.h"

TEST(Player, SubstractScore) {
    common::Player player("SpiderMan");
    player.SubstractScore(3);
    EXPECT_EQ(player.score(), -3);
}
