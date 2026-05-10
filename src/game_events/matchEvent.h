#ifndef MATCHEVENT_H
#define MATCHEVENT_H

#include "deck/deckEntry.h"
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

    void rewardPhase();

  private:
    IMatchView& m_matchView;
    EnemyId m_enemyId;
    std::string m_enemyName{};
    Player& m_player;
    const std::vector<DeckEntry> m_rewardCardList;
};

#endif // MATCHEVENT_H