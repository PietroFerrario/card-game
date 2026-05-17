#ifndef DECKENTRY_H
#define DECKENTRY_H

#include "cards/cardParams.h"

#include <string>

/**
 * @brief Represents a single card entry in the player's persistent deck.
 *
 * Each entry stores:
 * - The card's ID (matches a CardDefinition ID)
 * - The Run-Based modifiers stored in a CardParams
 *
 * Used for saving, loading, and modifying the player's deck outside of combat.
 */
struct DeckEntry
{
    std::string cardId;            ///< Identifier matching a CardDefinition.
    CardParams permanentModifiers; ///< Run-Based modifiers
};

#endif // DECKENTRY_H