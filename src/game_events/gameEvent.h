#ifndef GAMEEVENT_H
#define GAMEEVENT_H

#include "rewards/rewardPhase.h"

class GameEvent
{
  public:
    virtual ~GameEvent() = default;
    virtual void resolve() = 0;

  private:
    void resolveReward();
};

#endif // GAMEEVENT_H