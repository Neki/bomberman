#ifndef SRC_SERVER_NET_EMITTERVISITOR_H_
#define SRC_SERVER_NET_EMITTERVISITOR_H_

#include "GameNetworkWorker.h"
#include "BaseClientEvent.h"
#include "src/common/net/GameEventVisitor.h"

using namespace common::net;

namespace net {

class GameNetworkWorker; // forward declaration as GameNetworkWorker also includes EmitterVisitor (not an issue since these classes are tightly related)

class EmitterVisitor : public GameEventVisitor {

  public:
    EmitterVisitor(GameNetworkWorker* worker, BaseClientEvent* base_event);
    ~EmitterVisitor();

    void Visit(MoveEvent& event) override;
    void Visit(BombEvent& event) override;
    void Visit(PlayerLeftEvent& event) override;

  private:
    GameNetworkWorker* worker_;
    BaseClientEvent* base_event_;

};

}

#endif

