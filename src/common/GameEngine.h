#ifndef SRC_SERVER_GAMEENGINE_H_
#define SRC_SERVER_GAMEENGINE_H_

#include <QObject>
#include <QPoint>
#include "World.h"

namespace common {

class GameEngine : public QObject {
  Q_OBJECT
  public:
    
    void AddFireFromAtoB(QPoint a, QPoint b);
    
  private:

};

}

#endif /* end of include guard: SRC_SERVER_GAMEENGINE_H_ */