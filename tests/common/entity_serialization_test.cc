#include "gtest/gtest.h"

#include "src/common/entity/Block.h"
#include "src/common/entity/Bomb.h"
#include "src/common/entity/Bonus.h"
#include "src/common/entity/Character.h"
#include "src/common/entity/Fire.h"
#include "src/common/entity/Wall.h"
#include "src/common/net/Deserializer.h"

using namespace common::entity;
using namespace common::net;

TEST(EntitySerializationTest, Serialization) {
  QByteArray buffer;
  QDataStream in(&buffer, QIODevice::OpenModeFlag::WriteOnly);
  QDataStream out(&buffer, QIODevice::OpenModeFlag::ReadOnly);

  Block block(QPoint(1,2));
  in << block;
  auto block_out = Deserializer::DeserializeEntity(out);
  EXPECT_EQ(block, *static_cast<Block*>(block_out.get()));

  Bomb bomb(QPoint(3,4), 123, 456, 2);
  in << bomb;
  auto bomb_out = Deserializer::DeserializeEntity(out);
  EXPECT_EQ(bomb, *static_cast<Bomb*>(bomb_out.get()));

  Bonus bonus(QPoint(1,2));
  in << bonus;
  auto bonus_out = Deserializer::DeserializeEntity(out);
  EXPECT_EQ(bonus, *static_cast<Bonus*>(bonus_out.get()));

  Character character(QPoint(5,4), 2, 5, 3);
  in << character;
  auto character_out = Deserializer::DeserializeEntity(out);
  EXPECT_EQ(character, *static_cast<Character*>(character_out.get()));

  Fire fire(QPoint(8,9), 456);
  in << fire;
  auto fire_out = Deserializer::DeserializeEntity(out);
  EXPECT_EQ(fire, *static_cast<Fire*>(fire_out.get()));

  Wall wall(QPoint(5,4));
  in << wall;
  auto wall_out = Deserializer::DeserializeEntity(out);
  EXPECT_EQ(wall, *static_cast<Wall*>(wall_out.get()));
}
