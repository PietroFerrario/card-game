#include "deckCombat.h"
#include "cards/cardDefinition.h"
#include "cards/cardInstance.h"
#include "deckEntry.h"
#include "deckPlayer.h"
#include "factories/ICardFactory.h"
#include "util/Random.h"

#include "util/debug.h"

#include <algorithm>

DeckCombat::DeckCombat(const DeckPlayer& deck_player, const ICardFactory& factory)
    : m_factory{factory}
{
    populateDeck(deck_player.getCardList());
    shuffle();
}

void DeckCombat::populateDeck(const std::vector<DeckEntry>& cardList)
{
    for (const auto& deckEntry : cardList)
    {
        for (int i{0}; i < deckEntry.cardCount; ++i)
        {
            m_drawPile.emplace_back(m_factory.makeSingleCard(deckEntry.cardId));
        }
    }
}

DrawData DeckCombat::drawMultipleCards(int amount)
{
    DrawData currentDrawData;
    DEBUG_LOG("Requesting to draw " << amount << " cards from the deck: ...");
    for (int i{0}; i < amount; i++)
    {
        DrawResult drawResult{drawCard()};

        if (drawResult.cardDrawn)
        {
            currentDrawData.drawnCardsNames.push_back(
                drawResult.cardDrawn->getCardDefinition().getName());
        }
        else
        {
            break;
        }
        currentDrawData.reshuffled = currentDrawData.reshuffled || drawResult.reshuffled;
    }

    return currentDrawData;
}

DrawResult DeckCombat::drawCard()
{
    DrawResult drawResult;

    if (m_drawPile.empty())
    {
        DEBUG_LOG("The deck is empty: no more cards to drawn. Regenerating deck from discard pile");
        regenerateDeck();
        drawResult.reshuffled = true;
    }
    if (!m_drawPile.empty())
    {
        m_handPile.emplace_back(std::move(m_drawPile.back()));
        m_drawPile.pop_back();
        DEBUG_LOG("Drawn " << m_handPile.back()->getCardDefinition().getID()
                           << " from the deck, placed in the handPile.");
        drawResult.cardDrawn = m_handPile.back().get();
    }
    else
    {

        DEBUG_LOG("The deck and the discard pile are empty: no more cards to drawn");
    }

    return drawResult;
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
    if (handIndex < 0 || handIndex >= getHandSize())
    {
        DEBUG_LOG("The index " << handIndex << " is out of bounds.");
    }
    else
    {
        m_discardPile.emplace_back(std::move(m_handPile.at(handIndex)));
        m_handPile.erase(m_handPile.begin() + handIndex);
        DEBUG_LOG("Discarded " << m_discardPile.back()->getCardDefinition().getID()
                               << " from the handPile, and placed in the discardPile.");
    }
}

void DeckCombat::discardWholeHand()
{
    m_discardPile.insert(m_discardPile.end(), std::make_move_iterator(m_handPile.begin()),
                         std::make_move_iterator(m_handPile.end()));
    m_handPile.clear();
    DEBUG_LOG("Discarding the whole hand");
}

std::vector<const CardInstance*> DeckCombat::getHandView() const
{
    std::vector<const CardInstance*> handView;
    handView.reserve(m_handPile.size());

    for (const std::unique_ptr<CardInstance>& currentCard : m_handPile)
    {
        handView.emplace_back(currentCard.get());
    }

    return handView;
}

void DeckCombat::shuffle() { std::shuffle(m_drawPile.begin(), m_drawPile.end(), Random::mt); }

void DeckCombat::regenerateDeck()
{
    if (m_drawPile.empty() && !m_discardPile.empty())
    {
        m_drawPile = std::move(m_discardPile);
        m_discardPile.clear();
        shuffle();
    }
}