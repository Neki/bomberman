#include "gtest/gtest.h"
#include <memory>

#include "src/common/net/Deserializer.h"
#include "src/common/net/QuitReason.h"
#include <QByteArray>

using common::net::Deserializer;
using common::net::EventId;
using common::Direction;

class EventSerializationTest : public testing::Test {

  public:
    EventSerializationTest()
      :  testing::Test(),
         bomb_event_(common::net::BombEvent(QPoint(1,3), 1, 20, 20)),
         move_event_(common::net::MoveEvent(QPoint(0,8), QPoint(0,9), Direction::LEFT, 1, 20, 25)),
         joined_event_(common::net::PlayerJoinedEvent(QString("The mad bomber"), 20, 25)),
         left_event_(common::net::PlayerLeftEvent(common::net::QuitReason::TIMEOUT, 3, 15, 23)),
         admin_event_(common::net::SetAdminEvent(15, 23)) {
        event_id_map_[EventId::kBombEventId] = &bomb_event_;
        event_id_map_[EventId::kMoveEventId] = &move_event_;
        event_id_map_[EventId::kPlayerJoinedEvent] = &joined_event_;
        event_id_map_[EventId::kPlayerLeftEvent] = &left_event_;
        event_id_map_[EventId::kSetAdminEvent] = &admin_event_;
      }

  protected:
    common::net::BombEvent bomb_event_;
    common::net::MoveEvent move_event_;
    common::net::PlayerJoinedEvent joined_event_;
    common::net::PlayerLeftEvent left_event_;
    common::net::SetAdminEvent admin_event_;
    std::map<EventId, common::net::Event*> event_id_map_;
};

TEST_F(EventSerializationTest, EventId) {
  QByteArray buffer;
  QDataStream in(&buffer, QIODevice::OpenModeFlag::WriteOnly);
  QDataStream out(&buffer, QIODevice::OpenModeFlag::ReadOnly);

  for(auto p : event_id_map_) {
    in << *p.second;
    EventId id = Deserializer::GetNextEventId(out);
    EXPECT_EQ(p.first, id);
    out.device()->readAll(); // clear the remaining data in the buffer
  }
}

TEST_F(EventSerializationTest, Event) {
  QByteArray buffer;
  QDataStream in(&buffer, QIODevice::OpenModeFlag::WriteOnly);
  QDataStream out(&buffer, QIODevice::OpenModeFlag::ReadOnly);

  for(auto p : event_id_map_) {
    in << *p.second;
    Deserializer::GetNextEventId(out);
    switch(p.first) {
      case EventId::kBombEventId:
        EXPECT_EQ(*static_cast<common::net::BombEvent*>(p.second), Deserializer::DeserializeBombEvent(out));
        break;
      case EventId::kMoveEventId:
        EXPECT_EQ(*static_cast<common::net::MoveEvent*>(p.second), Deserializer::DeserializeMoveEvent(out));
        break;
      case EventId::kPlayerJoinedEvent:
        EXPECT_EQ(*static_cast<common::net::PlayerJoinedEvent*>(p.second), Deserializer::DeserializePlayerJoinedEvent(out));
        break;
      case EventId::kPlayerLeftEvent:
        EXPECT_EQ(*static_cast<common::net::PlayerLeftEvent*>(p.second), Deserializer::DeserializePlayerLeftEvent(out));
        break;
      case EventId::kSetAdminEvent:
        EXPECT_EQ(*static_cast<common::net::SetAdminEvent*>(p.second), Deserializer::DeserializeSetAdminEvent(out));
        break;
      case EventId::kSettingsEvent:
        EXPECT_EQ(*static_cast<common::net::SettingsEvent*>(p.second), Deserializer::DeserializeSettingsEvent(out));
        break;
      case EventId::kUnknownEventId:
        FAIL() << "Unknown event deserialized";
        break;
    }
  }
}

TEST(InGameSerializationTest, InGameEvent) {
  QByteArray buffer;
  QDataStream in(&buffer, QIODevice::OpenModeFlag::WriteOnly);
  QDataStream out(&buffer, QIODevice::OpenModeFlag::ReadOnly);
  std::unique_ptr<common::net::InGameEvent> bomb_event(new common::net::BombEvent(QPoint(5,5), 2, 12, 45));
  std::unique_ptr<common::net::InGameEvent> move_event(new common::net::MoveEvent(QPoint(5,5), QPoint(0,9), Direction::UP, 2, 45, 42));
  std::unique_ptr<common::net::InGameEvent> left_event(new common::net::PlayerLeftEvent(common::net::QuitReason::LEFT_GAME, 3, 45, 42));
  in << *bomb_event.get();
  EXPECT_EQ(*static_cast<common::net::BombEvent*>(bomb_event.get()), *static_cast<common::net::BombEvent*>(Deserializer::DeserializeInGameEvent(out).get()));
  in << *move_event.get();
  EXPECT_EQ(*static_cast<common::net::MoveEvent*>(move_event.get()), *static_cast<common::net::MoveEvent*>(Deserializer::DeserializeInGameEvent(out).get()));
  in << *left_event.get();
  EXPECT_EQ(*static_cast<common::net::PlayerLeftEvent*>(left_event.get()), *static_cast<common::net::PlayerLeftEvent*>(Deserializer::DeserializeInGameEvent(out).get()));
}
