#ifndef DECKCOMBAT_H
#define DECKCOMBAT_H

#include <memory>
#include <string>
#include <vector>

class DeckPlayer;
class DeckEntry;
class CardInstance;
class ICardFactory;

/**
 * @brief Manages all card piles during a single combat.
 *
 * DeckCombat is the runtime deck system used during an encounter.
 * It is initialized from the player's persistent DeckPlayer and builds
 * a fresh set of CardInstances using the provided ICardFactory.
 *
 * It owns and manages:
 * - Draw pile (main deck)
 * - Hand pile (cards in hand)
 * - Discard pile (used cards)
 *
 * Cards are never duplicated. Ownership moves between piles via std::move.
 * The deck is destroyed at the end of combat.
 */
class DeckCombat
{
  public:
    /**
     * @brief Constructs the combat deck from a player's persistent deck.
     *
     * Creates runtime CardInstances for each entry in the DeckPlayer.
     *
     * @param deck_player The source persistent deck.
     * @param factory Card creation system used to instantiate CardInstances.
     */
    DeckCombat(const DeckPlayer& deck_player, const ICardFactory& factory);

    /**
     * @brief Draws one card from the draw pile to the hand.
     *
     * If the draw pile is empty, no action is taken.
     */
    void drawCard();

    /**
     * @brief Discards a card from the hand to the discard pile.
     *
     * @param handIndex Index of the card in the hand pile.
     * If index is out of bounds, no action is taken.
     */
    void discardFromHand(int handIndex);

    int getHandSize() const { return m_handPile.size(); }

    bool isValidHandIndex(int index) const;

    void discard(std::unique_ptr<CardInstance> exhaustedCard);

    std::unique_ptr<CardInstance> takeFromHand(int index);

    CardInstance& getCardInHand(int index) { return *m_handPile[index]; }
    /// @brief Returns a reference to the current hand pile.
    std::vector<std::unique_ptr<CardInstance>>& getHandPile() { return m_handPile; }
    std::vector<const CardInstance*> getHandView();

  private:
    std::vector<std::unique_ptr<CardInstance>> m_cards;       ///< Draw pile (initial deck).
    std::vector<std::unique_ptr<CardInstance>> m_handPile;    ///< Cards in hand.
    std::vector<std::unique_ptr<CardInstance>> m_discardPile; ///< Used/discarded cards.

    const ICardFactory& m_factory; ///< Reference to the card creation system.

    /**
     * @brief Populates the draw pile by creating instances from the deck list.
     *
     * One CardInstance is created for each copy listed in the DeckEntry vector.
     *
     * @param cardList List of DeckEntries from the player's deck.
     */
    void populateDeck(const std::vector<DeckEntry>& cardList);
};

#endif // DECKCOMBAT_H
