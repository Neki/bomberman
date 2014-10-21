#include "gtest/gtest.h"
#include <memory>

#include "src/common/net/Deserializer.h"
#include <QByteArray>

using common::net::Deserializer;
using common::net::EventId;

class SerializationTest : public testing::Test {

  public:
    SerializationTest()
      :  testing::Test(),
         bomb_event_(common::net::BombEvent(QPoint(1,3), 20, 20)),
         move_event_(common::net::MoveEvent(QPoint(0,8), Direction::LEFT, 20, 25)),
         joined_event_(common::net::PlayerJoinedEvent(QString("The mad bomber"), 20, 25)),
         left_event_(common::net::PlayerLeftEvent(common::net::QuitReason::TIMEOUT, 15, 23)),
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

TEST_F(SerializationTest, EventId) {
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

TEST_F(SerializationTest, Event) {
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

TEST_F(SerializationTest, GenericEvent) {
  QByteArray buffer;
  QDataStream in(&buffer, QIODevice::OpenModeFlag::WriteOnly);
  QDataStream out(&buffer, QIODevice::OpenModeFlag::ReadOnly);
  for(auto p : event_id_map_) {
    in << *p.second;
    auto event = Deserializer::DeserializeEvent(out);
    EXPECT_EQ(*p.second, *event.get());
  }
}
