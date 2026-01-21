#include "deck/deckPlayer.h"
#include "util/debug.h"

#include <algorithm>

DeckPlayer::DeckPlayer(std::vector<DeckEntry> startingCardList, int maxCardNumber)
    : m_cardsList{std::move(startingCardList)}, m_maxCardNumber{maxCardNumber}
{
}

std::ostream &operator<<(std::ostream &out, const DeckPlayer &deck)
{
    for (auto &card : deck.m_cardsList)
    {
        out << "id: " << card.cardId << " - count: " << card.cardCount << "\t \t";
    }

    out << "\n";

    return out;
}

int DeckPlayer::getCurrentCardNumber() const
{
    int cardCount{};
    for (const auto &el : m_cardsList)
    {
        cardCount += el.cardCount;
    }

    return cardCount;
}

bool DeckPlayer::isCardPresent(std::string_view cardId) const
{
    auto it = std::find_if(m_cardsList.begin(), m_cardsList.end(), [cardId](const DeckEntry &deckEntry)
                           { return deckEntry.cardId == cardId; });

    return (it != m_cardsList.end());
}

bool DeckPlayer::addCard(std::string_view cardId)
{
    if (getCurrentCardNumber() < m_maxCardNumber)
    {
        auto it = std::find_if(m_cardsList.begin(), m_cardsList.end(), [cardId](const DeckEntry &deckEntry)
                               { return deckEntry.cardId == cardId; });
        if (it != m_cardsList.end())
        {
            it->cardCount++;
            DEBUG_LOG("Added an already existing card to the deck: " << cardId);
        }
        else
        {
            m_cardsList.emplace_back(DeckEntry{std::string{cardId}, 1});
            DEBUG_LOG("Added a new card to the deck: " << cardId);
        }
        return true;
    }
    else
        return false;
}

bool DeckPlayer::removeCard(std::string_view cardId)
{
    if (getCurrentCardNumber() > m_minCardNumber)
    {
        auto it = std::find_if(m_cardsList.begin(), m_cardsList.end(), [cardId](const DeckEntry &deckEntry)
                               { return deckEntry.cardId == cardId; });
        if (it != m_cardsList.end())
        {
            it->cardCount--;
            DEBUG_LOG("Removed a card from the deck: " << cardId);
            if (it->cardCount == 0)
            {
                it = m_cardsList.erase(it);
                DEBUG_LOG("No more " << cardId << " left in the deck");
            }
            return true;
        }
        else
        {
            DEBUG_LOG("Tried to remove a card that is not in the deck: " << cardId);
        }
    }
    else
    {
        DEBUG_LOG("You can't remove cards anymore, your deck is too small");
    }
    return false;
}
