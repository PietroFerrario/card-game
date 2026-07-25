#ifndef GAINCARDREWARDEFFECT_H
#define GAINCARDREWARDEFFECT_H

#include "deck/deckPlayer.h"
#include "game_events/rewards/rewardContext.h"
#include "rewardEffect.h"

#include <string>

class GainCardRewardEffect : public RewardEffect
{

  public:
    GainCardRewardEffect(std::string_view cardId) : m_cardId{cardId} {}

    void resolve(RewardContext& rewardContext) override
    {
        rewardContext.player.addCardToDeck(m_cardId,
                                           rewardContext.cardFactory.getCardPopulation(m_cardId));
    };

  private:
    std::string m_cardId;
};

#endif // GAINCARDREWARDEFFECT_H
