#include "deckCombat.h"
#include "cards/cardDefinition.h"
#include "cards/cardInstance.h"
#include "deckEntry.h"
#include "deckPlayer.h"
#include "factories/ICardFactory.h"

#include "util/debug.h"

DeckCombat::DeckCombat(const DeckPlayer& deck_player, const ICardFactory& factory)
    : m_factory{factory}
{
    populateDeck(deck_player.getCardList());
}

void DeckCombat::populateDeck(const std::vector<DeckEntry>& cardList)
{
    for (const auto& deckEntry : cardList)
    {
        for (int i{0}; i < deckEntry.cardCount; ++i)
        {
            m_cards.emplace_back(m_factory.makeSingleCard(deckEntry.cardId));
        }
    }
}

void DeckCombat::drawCard()
{
    if (!m_cards.empty())
    {
        m_handPile.emplace_back(std::move(m_cards.back()));
        m_cards.pop_back();
        DEBUG_LOG("Drawn " << m_handPile.back()->getCardDefinition().getID()
                           << " from the deck, placed in the handPile.");
    }
    else
    {
        DEBUG_LOG("The deck is empty: no more cards to drawn.");
    }
}

std::unique_ptr<CardInstance> DeckCombat::takeFromHand(int index)
{
    if (index < 0 || index >= getHandSize())
    {
        DEBUG_LOG("Invalid inxex: " << index);
        return nullptr;
    }
    else
    {
        DEBUG_LOG("Took a card from hand");
        std::unique_ptr<CardInstance> cardToMove{std::move(m_handPile[index])};
        m_handPile.erase(m_handPile.begin() + index);
        return cardToMove;
    }
}

void DeckCombat::discard(std::unique_ptr<CardInstance> Card)
{
    if (!Card)
    {
        return;
    }
    DEBUG_LOG("Moved the exhausted card to the discard pile");
    m_discardPile.emplace_back(std::move(Card));
}

void DeckCombat::discardFromHand(int handIndex)
{
    if (m_handPile.size() > handIndex)
    {
        m_discardPile.emplace_back(std::move(m_handPile.at(handIndex)));
        m_handPile.erase(m_handPile.begin() + handIndex);
        DEBUG_LOG("Discarded " << m_discardPile.back()->getCardDefinition().getID()
                               << " from the handPile, and placed in the discardPile.");
    }
    else
    {
        DEBUG_LOG("The index " << handIndex << " is out of bounds.");
    }
}

std::vector<const CardInstance*> DeckCombat::getHandView()
{
    std::vector<const CardInstance*> handView;
    handView.reserve(m_handPile.size());

    for (const std::unique_ptr<CardInstance>& currentCard : m_handPile)
    {
        handView.emplace_back(currentCard.get());
    }

    return handView;
}