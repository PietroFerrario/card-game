#ifndef CARDFACTORY_H
#define CARDFACTORY_H

#include "ICardFactory.h"

#include <string_view>
#include <unordered_map>

class CardDefinition;
class CardInstance;

/**
 * @brief Central factory for creating CardInstances from registered definitions.
 *
 * CardFactory owns all immutable CardDefinitions used during combat.
 * It is responsible for:
 * - Registering cards at startup
 * - Storing definitions mapped by unique ID
 * - Creating new CardInstances from definitions
 *
 * CardFactory is only responsible for card data and instantiation; not for deck or match logic.
 */
class CardFactory : public ICardFactory
{
  public:
    /// @brief Constructs and registers all cards at startup.
    CardFactory();

    /**
     * @brief Registers a new card definition.
     *
     * Adds the CardDefinition to the internal map, keyed by its unique ID.
     * If the ID is already present, the definition is not replaced.
     *
     * @param cardId Unique string identifier for the card.
     * @param uniqueCardDefinition Ownership of the new definition.
     */
    void registerDefinition(std::string_view cardId,
                            std::unique_ptr<CardDefinition> uniqueCardDefinition);

    /**
     * @brief Populates the factory with all static card definitions.
     *
     * Called during construction.
     */
    void registerCards();

    /**
     * @brief Creates a new CardInstance based on the registered definition.
     *
     * Looks up the card ID and returns a runtime copy (CardInstance).
     * Throws if the ID is not registered.
     *
     * @param cardId ID of the card to create.
     * @return A unique_ptr to the new CardInstance.
     */
    std::unique_ptr<CardInstance> makeSingleCard(const std::string& cardId) const override;

    /// @brief Destructor.
    ~CardFactory();

  private:
    /// @brief Map of all registered card definitions, keyed by ID.
    std::unordered_map<std::string, std::unique_ptr<CardDefinition>> m_cardMap;
};

#endif // CARDFACTORY_H