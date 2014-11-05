#include "gtest/gtest.h"
#include "src/common/Game.h"

TEST(Game, AddPlayer) {
    common::Game game;
    common::Player player("SpiderMan");
    EXPECT_EQ(game.GetPlayersCount(), 0);
    game.AddPlayer(player);
    EXPECT_EQ(game.GetPlayersCount(), 1);
}

TEST(Game, GetPlayer) {
    common::Game game;
    common::Player player("IronMan");
    int player_id = game.AddPlayer(player);

    common::Player *new_player = game.GetPlayer(player_id);
    EXPECT_EQ(new_player->GetName(), player.GetName());

    EXPECT_THROW(game.GetPlayer(40), std::exception);
}
