#include "cardmatch.h"
#include "cards/CardInstance.h"
#include "cards/cardDefinition.h"
#include "cards/effect.h"
#include "entities/enemies/enemy.h"
#include "entities/player.h"

CardMatch::CardMatch(Player& player, Enemy& enemy)
    : m_player{player}, m_enemy{enemy}, m_cardFactory{},
      m_deckCombat{m_player.getDeckPlayer(), m_cardFactory}
{
}

void CardMatch::gainArmor(int defense) { m_player.increaseArmor(defense); }

void CardMatch::playCard(int handIndex)
{
    std::unique_ptr<CardInstance>& cardToPlay = m_deckCombat.getHandPile()[handIndex];

    for (const auto& effectPtr : cardToPlay->getCardDefinition().getEffectList())
    {
        effectPtr->apply(*this, *cardToPlay);
    }

    m_deckCombat.discardFromHand(handIndex);
}