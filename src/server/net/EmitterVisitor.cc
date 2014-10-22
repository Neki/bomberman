#include "EmitterVisitor.h"

using namespace common::net;

namespace net {

EmitterVisitor::EmitterVisitor(GameNetworkWorker* worker, BaseClientEvent* base_event)
  : worker_(worker),
    base_event_(base_event) {
}

EmitterVisitor::~EmitterVisitor() {}

void EmitterVisitor::Visit(MoveEvent& event) {
  auto client_event = ClientEvent<MoveEvent>(event, base_event_->GetClient(), base_event_->GetServerTimestamp());
  worker_->EmitEvent(client_event);
}

void EmitterVisitor::Visit(BombEvent& event) {
  auto client_event = ClientEvent<BombEvent>(event, base_event_->GetClient(), base_event_->GetServerTimestamp());
  worker_->EmitEvent(client_event);
}

void EmitterVisitor::Visit(PlayerLeftEvent& event) {
  auto client_event = ClientEvent<PlayerLeftEvent>(event, base_event_->GetClient(), base_event_->GetServerTimestamp());
  worker_->EmitEvent(client_event);
}

}
