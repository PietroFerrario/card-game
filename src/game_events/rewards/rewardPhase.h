#ifndef REWARDPHASE_H
#define REWARDPHASE_H

#include "cards/cardInstance.h"
#include "deck/deckEntry.h"
#include "entities/player.h"
#include "factories/ICardFactory.h"
#include "rewardOption.h"
#include "ui/IRewardView.h"
#include "util/Random.h"

#include <string_view>
#include <vector>

class RewardPhase
{
  public:
    explicit RewardPhase(IRewardView& rewardView, Player& player, ICardFactory& cardFactory,
                         std::string_view enemyName, std::vector<RewardOption>& rewardOptionList);

    void execute();

  private:
    void getPlayerDecision();
    void showRewardOptions();
    void resolveReward();
    void resolveOptionEffects(int optionsIndex);

    void askPlayerCardChoice();
    std::vector<std::unique_ptr<CardInstance>> generateRandomCards(int amount);

    Player& m_player;
    ICardFactory& m_cardFactory;
    std::string_view m_enemyName;
    std::vector<RewardOption>& m_rewardOptionList;
    IRewardView& m_rewardView;
};

#endif // REWARDPHASE_H
