#include "gtest/gtest.h"
#include "src/common/Game.h"
#include <memory>
#include <QString>

TEST(Game, AddPlayer) {
    common::Game game;
    std::shared_ptr<common::Player> player (new common::Player(1, "SpiderMan"));
    EXPECT_EQ(game.GetPlayersCount(), 0);
    game.AddPlayer(player);
    EXPECT_EQ(game.GetPlayersCount(), 1);
}

TEST(Game, GetPlayer) {
    common::Game game;
    std::shared_ptr<common::Player> player(new common::Player(2, "IronMan"));
    game.AddPlayer(player);
    std::weak_ptr<common::Player> get_player = game.GetPlayer(2);
    std::shared_ptr<common::Player> new_player = get_player.lock();
    EXPECT_EQ(new_player->GetName(), player->GetName());
}
