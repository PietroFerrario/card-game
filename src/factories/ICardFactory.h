#ifndef ICARDFACTORY_H
#define ICARDFACTORY_H

#include "deck/deckEntry.h"

#include <memory>
#include <string>

class CardDefinition;
class CardInstance;

/**
 * @brief Interface for card instance creation.
 *
 * ICardFactory defines the contract used by runtime systems (e.g., DeckCombat)
 * to create CardInstances without depending on a concrete factory implementation.
 */
class ICardFactory
{
  public:
    /**
     * @brief Creates a new CardInstance identified by the given card ID.
     *
     * @param cardId Identifier of the card to instantiate.
     * @return Owned CardInstance.
     */
    virtual std::unique_ptr<CardInstance> makeSingleCard(const DeckEntry& deckEntry) const = 0;

    /// @brief Virtual destructor.
    virtual ~ICardFactory() = default;
};

#endif // CARDFACTORY_H