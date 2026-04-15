#ifndef MATCHEVENT_H
#define MATCHEVENT_H

#include "entities/enemies/enemy.h"
#include "entities/player.h"
#include "factories/enemyFactory.h"
#include "gameEvent.h"
#include "ui/IMatchView.h"

#include <memory>

class MatchEvent : public GameEvent
{
  public:
    MatchEvent(IMatchView& matchView, Player& player, EnemyId enemyId);

    void resolve() override;

  private:
    IMatchView& m_matchView;
    EnemyId m_enemyId;
    Player& m_player;
};

#endif // MATCHEVENT_H