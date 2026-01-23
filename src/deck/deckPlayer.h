#ifndef DECKPLAYER_H
#define DECKPLAYER_H

#include "deckEntry.h"

#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

/**
 * @brief Represents the player's persistent deck outside of combat.
 *
 * DeckPlayer stores card ownership data between matches.
 * It does not contain CardInstances — only card IDs and counts.
 *
 * Modifiable by rewards, progression, or deck editing.
 * Serialized separately from combat systems.
 */
class DeckPlayer
{
  public:
    /// @brief Constructs an empty deck.
    DeckPlayer() {}
    /**
     * @brief Constructs a deck from an initial list of entries.
     *
     * @param startingCardList Initial list of card IDs and quantities.
     * @param maxCardNumbers Maximum total card count allowed.
     */
    DeckPlayer(std::vector<DeckEntry> startingCardList, int maxCardNumbers = 20);

    /// @brief Outputs the deck contents to an output stream.
    friend std::ostream& operator<<(std::ostream& out, const DeckPlayer& deck);

    /// @brief Returns the total number of cards (sum of all counts).
    int getCurrentCardNumber() const;
    /**
     * @brief Checks if a card ID is present in the deck.
     *
     * @param cardId ID to search for.
     * @return true if at least one copy exists, false otherwise.
     */
    bool isCardPresent(std::string_view cardId) const;

    /**
     * @brief Adds a card to the deck, if below max size.
     *
     * If the card already exists, increments its count.
     *
     * @param cardId ID of the card to add.
     * @return true if added, false if deck is full.
     */
    bool addCard(std::string_view cardId);
    /**
     * @brief Removes one copy of a card, if above minimum size.
     *
     * If the last copy is removed, the entry is erased entirely.
     *
     * @param cardId ID of the card to remove.
     * @return true if removed, false otherwise.
     */
    bool removeCard(std::string_view cardId);

    /// @brief Returns the full list of card entries.
    const std::vector<DeckEntry>& getCardList() const { return m_cardsList; }

  private:
    int m_maxCardNumber{};                ///< Maximum allowed total cards.
    int m_minCardNumber{5};               ///< Minimum cards required to keep a valid deck.
    std::vector<DeckEntry> m_cardsList{}; ///< List of card ID + count pairs.
};

#endif // DECKPLAYER_H