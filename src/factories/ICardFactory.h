#ifndef ICARDFACTORY_H
#define ICARDFACTORY_H

#include "deck/deckEntry.h"

#include <memory>
#include <string>
#include <string_view>
#include <vector>

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

    virtual void registerCards() = 0;

    virtual std::vector<std::string> getRegisteredCardsId() const = 0;

    virtual int getCardPopulation(std::string_view cardId) const = 0;
    virtual std::string_view getCardName(std::string_view cardId) const = 0;
    /// @brief Virtual destructor.
    virtual ~ICardFactory() = default;
};

#endif // CARDFACTORY_H
