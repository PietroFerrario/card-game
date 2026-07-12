#ifndef MATCHEVENT_H
#define MATCHEVENT_H

#include "deck/deckEntry.h"
#include "entities/enemies/enemyId.h"
#include "entities/player.h"
#include "factories/enemyFactory.h"
#include "gameEvent.h"
#include "ui/IMatchView.h"
#include "ui/IRewardView.h"

#include <string>
#include <vector>
class ICardFactory;

class MatchEvent : public GameEvent
{
  public:
    MatchEvent(IMatchView& matchView, IRewardView& rewardView, ICardFactory& cardFactory,
               EnemyFactory& enemyFactory, Player& player, std::string enemyId,
               std::vector<RewardOption> rewardOptionList);

    void resolve() override;

  private:
    IMatchView& m_matchView;
    IRewardView& m_rewardView;
    ICardFactory& m_cardFactory;
    EnemyFactory& m_enemyFactory;

    std::string m_enemyId;
    std::string m_enemyName{};
    Player& m_player;
    std::vector<RewardOption> m_rewardOptionList;
};

#endif // MATCHEVENT_H
