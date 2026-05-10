#ifndef MATCHEVENT_H
#define MATCHEVENT_H

#include "deck/deckEntry.h"
#include "entities/enemies/enemyId.h"
#include "entities/player.h"
#include "factories/enemyFactory.h"
#include "gameEvent.h"
#include "ui/IMatchView.h"
#include "ui/IRewardView.h"

#include <memory>
#include <vector>

class MatchEvent : public GameEvent
{
  public:
    MatchEvent(IMatchView& matchView, IRewardView& rewardView, Player& player, EnemyId enemyId,
               std::vector<RewardOption> rewardOptionList);

    void resolve() override;

    void rewardPhase();

  private:
    IMatchView& m_matchView;
    IRewardView& m_rewardView;
    EnemyId m_enemyId;
    std::string m_enemyName{};
    Player& m_player;
    std::vector<RewardOption> m_rewardOptionList;
};

#endif // MATCHEVENT_H