#ifndef GAINCARDREWARDEFFECT_H
#define GAINCARDREWARDEFFECT_H

#include "deck/deckPlayer.h"
#include "rewardEffect.h"

#include <string>

class GainCardRewardEffect : public RewardEffect
{

  public:
    GainCardRewardEffect(std::string_view cardId) : m_cardId{cardId} {}

    void resolve(Player& player) override { player.getDeckPlayer().addCard(m_cardId); };

  private:
    std::string m_cardId;
};

#endif // GAINCARDREWARDEFFECT_H
