#include "deckPlayer.h"

#include <algorithm>

DeckPlayer::DeckPlayer(std::vector<DeckEntry> &starting_card_list)
    : m_cards_list{std::move(starting_card_list)} {}

std::ostream &operator<<(std::ostream &out, const DeckPlayer &deck)
{
    for (auto &card : deck.m_cards_list)
    {
        std::cout << "id: " << card.card_id << ", #: " << card.card_count << "\t";
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
        }
        else
        {
            m_cards_list.emplace_back(DeckEntry{std::string{card_id}, 1});
        }
        return true;
    }
    else
        return false;
}
