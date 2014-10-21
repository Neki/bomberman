#ifndef SRC_SERVER_NET_EVENTVISITOR_H_
#define SRC_SERVER_NET_EVENTVISITOR_H_

namespace common {
namespace net {

class BombEvent;
class PlayerLeftEvent;
class MoveEvent;

class GameEventVisitor {

  public:
    virtual void Visit(MoveEvent& event) = 0;
    virtual void Visit(BombEvent& event) = 0;
    virtual void Visit(PlayerLeftEvent& event) = 0;
    virtual ~GameEventVisitor() {}

};

}
}

#endif

