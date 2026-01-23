#ifndef DECKENTRY_H
#define DECKENTRY_H

#include <string>

/**
 * @brief Represents a single card entry in the player's persistent deck.
 *
 * Each entry stores:
 * - The card's ID (matches a CardDefinition ID)
 * - The number of copies the player owns
 *
 * Used for saving, loading, and modifying the player's deck outside of combat.
 */
struct DeckEntry
{
    std::string cardId; ///< Identifier matching a CardDefinition.
    int cardCount;      ///< Number of copies owned.
};

#endif // DECKENTRY_H