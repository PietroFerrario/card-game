#include "deckPlayer.h"
#include "util/debug.h"

#include <algorithm>

DeckPlayer::DeckPlayer(std::vector<DeckEntry> &starting_card_list, int max_card_number)
    : m_cards_list{std::move(starting_card_list)}, m_max_card_number{max_card_number}
{
}

std::ostream &operator<<(std::ostream &out, const DeckPlayer &deck)
{
    for (auto &card : deck.m_cards_list)
    {
        std::cout << "id: " << card.card_id << " - count: " << card.card_count << "\t \t";
    }

    std::cout << std::endl;

    return out;
}

const int DeckPlayer::getCurrentCardNumber() const
{
    int card_count{};
    for (const auto &el : m_cards_list)
    {
        card_count += el.card_count;
    }

    return card_count;
}

bool DeckPlayer::isCardPresent(std::string_view card_id) const
{
    auto it = std::find_if(m_cards_list.begin(), m_cards_list.end(), [card_id](const DeckEntry &deck_entry)
                           { return deck_entry.card_id == card_id; });

    return (it != m_cards_list.end());
}

bool DeckPlayer::addCard(std::string_view card_id)
{
    if (getCurrentCardNumber() < m_max_card_number)
    {
        auto it = std::find_if(m_cards_list.begin(), m_cards_list.end(), [card_id](const DeckEntry &deck_entry)
                               { return deck_entry.card_id == card_id; });
        if (it != m_cards_list.end())
        {
            it->card_count++;
            DEBUG_LOG("Added an already existing card to the deck: " << card_id);
        }
        else
        {
            m_cards_list.emplace_back(DeckEntry{std::string{card_id}, 1});
            DEBUG_LOG("Added a new card to the deck: " << card_id);
        }
        return true;
    }
    else
        return false;
}

bool DeckPlayer::removeCard(std::string_view card_id)
{
    if (getCurrentCardNumber() > m_min_card_number)
    {
        auto it = std::find_if(m_cards_list.begin(), m_cards_list.end(), [card_id](const DeckEntry &deck_entry)
                               { return deck_entry.card_id == card_id; });
        if (it != m_cards_list.end())
        {
            it->card_count--;
            DEBUG_LOG("Removed a card from the deck: " << card_id);
            if (it->card_count == 0)
            {
                it = m_cards_list.erase(it);
                DEBUG_LOG("No more " << card_id << " left in the deck");
            }
            return true;
        }
        else
        {
            DEBUG_LOG("Tried to remove a card that is not in the deck: " << card_id);
        }
    }
    else
    {
        DEBUG_LOG("You can't remove cards anymore, your deck is too small");
    }
    return false;
}
