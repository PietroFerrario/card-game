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
        int cardPopulation{rewardContext.cardFactory.getCardPopulation(m_cardId)};
        if (rewardContext.player.addCardToDeck(m_cardId, cardPopulation))
        {
            rewardContext.rewardView.showAddedCard(
                rewardContext.cardFactory.getCardName(m_cardId),
                rewardContext.player.getDeckPlayer().getDeckSize());
            if (cardPopulation > 0)
            {

                rewardContext.rewardView.showNumbericalGainSummaryEffect(
                    cardPopulation, rewardContext.player.getPopulation(),
                    std::string{"population"});
            }
        }
    };

  private:
    std::string m_cardId;
};

#endif // GAINCARDREWARDEFFECT_H
