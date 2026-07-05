#include "deck/deckPlayer.h"
#include "util/debug.h"

#include <algorithm>

DeckPlayer::DeckPlayer(std::vector<DeckEntry> startingCardList, int maxCardNumber)
    : m_cardsList{std::move(startingCardList)}, m_maxCardNumber{maxCardNumber}
{
}

int DeckPlayer::getCurrentCardNumber() const { return static_cast<int>(m_cardsList.size()); }

bool DeckPlayer::isCardPresent(std::string_view cardId) const
{
    auto it =
        std::find_if(m_cardsList.begin(), m_cardsList.end(),
                     [cardId](const DeckEntry& deckEntry) { return deckEntry.cardId == cardId; });

    return (it != m_cardsList.end());
}

bool DeckPlayer::addCard(std::string_view cardId)
{
    if (getCurrentCardNumber() < m_maxCardNumber)
    {

        m_cardsList.emplace_back(DeckEntry{std::string{cardId}});
        DEBUG_LOG("Added a new card to the deck: " << cardId);
        return true;
    }

    else
        return false;
}

void DeckPlayer::upgradeCard(DeckEntry& cardToUpgrade, int amount,
                             std::vector<UpgradeCardParam> upgradeCardParam)
{
    for (auto& up : upgradeCardParam)
    {
        cardToUpgrade.permanentModifiers += convertUpgradeCardParam(amount, up);
    }
}

CardParams DeckPlayer::convertUpgradeCardParam(int amount, UpgradeCardParam upgradeCardParam)
{

    switch (upgradeCardParam)
    {
    case UpgradeCardParam::Attack:
        return {.damage = amount};
    case UpgradeCardParam::Armor:
        return {.armor = amount};
    case UpgradeCardParam::Action:
        return {.actions = amount};
    case UpgradeCardParam::Drawing:
        return {.drawing = amount};
    default:
        return {};
    }
}

DeckEntry& DeckPlayer::getCardEntry(int cardIndex) { return m_cardsList.at(cardIndex); }

// bool DeckPlayer::removeCard(std::string_view cardId)
// {
//     if (getCurrentCardNumber() > m_minCardNumber)
//     {
//         auto it = std::find_if(m_cardsList.begin(), m_cardsList.end(),
//                                [cardId](const DeckEntry& deckEntry)
//                                { return deckEntry.cardId == cardId; });
//         if (it != m_cardsList.end())
//         {
//             it->cardCount--;
//             DEBUG_LOG("Removed a card from the deck: " << cardId);
//             if (it->cardCount == 0)
//             {
//                 it = m_cardsList.erase(it);
//                 DEBUG_LOG("No more " << cardId << " left in the deck");
//             }
//             return true;
//         }
//         else
//         {
//             DEBUG_LOG("Tried to remove a card that is not in the deck: " << cardId);
//         }
//     }
//     else
//     {
//         DEBUG_LOG("You can't remove cards anymore, your deck is too small");
//     }
//     return false;
// }
