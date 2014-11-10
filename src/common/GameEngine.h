#ifndef SRC_SERVER_GAMEENGINE_H_
#define SRC_SERVER_GAMEENGINE_H_

#include <QObject>
#include <QPoint>
#include <QTimer>
#include <vector>

#include "src/common/net/MoveEvent.h"
#include "src/common/net/BombEvent.h"
#include "src/common/net/MoveEvent.h"
#include "src/common/net/GameEventVisitor.h"
#include "World.h"
#include "Player.h"
#include "entity/Entity.h"
#include "GameTimer.h"


namespace common {

  class GameEngine : public QObject, public net::GameEventVisitor {
  Q_OBJECT

  public:
    GameEngine();
    ~GameEngine();

    void AddPlayer(std::unique_ptr<Player> player);
    bool AddEntity(std::unique_ptr<entity::Entity> e); // TODO: should be private?
    void StartGame();
    quint32 GetTimestamp() const;
    /* Returns the number of milliseconds that have elapsed since the last time StartGame() was called. */
    World* GetWorld() const;
    void AddFireFromAtoB(QPoint a, QPoint b);

  private slots:
    void Update(int t); // t in ms. t is the duration of the frame

  private:
    bool AddFire(QPoint a); // return false if the case blocks fire

    void ChallengeStrategies();
    void Simulate(int t); // t in ms. t is the duration of the frame

    void SendGameState();

    void Visit(net::MoveEvent& event);
    void Visit(net::BombEvent& event);
    void Visit(net::PlayerLeftEvent& event);
    void MoveCharacter(int player_id, QPoint target);

    quint32 max_duration_; // in milliseconds

    std::vector<std::unique_ptr<Player> > players_;
    std::unique_ptr<World> world_;

    GameTimer game_timer_;
    std::unique_ptr<QTimer> new_frame_timer_;

    bool is_running_;
};

}

#endif /* end of include guard: SRC_SERVER_GAMEENGINE_H_ */

