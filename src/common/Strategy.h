#ifndef SRC_COMMON_STRATEGY_H_
#define SRC_COMMON_STRATEGY_H_

namespace common {

class Strategy
{
  public:
    Strategy(int id);
    virtual ~Strategy();

  private:
    int const character_id_; // Id of the character that is controlled by this Strategy
};

}

#endif