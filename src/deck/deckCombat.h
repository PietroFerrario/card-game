#ifndef DECKCOMBAT_H
#define DECKCOMBAT_H

#include "drawData.h"

#include <memory>
#include <string>
#include <string_view>
#include <vector>

class DeckPlayer;
class DeckEntry;
class CardInstance;
class ICardFactory;

struct DrawResult
{
    bool reshuffled{false};
    const CardInstance* cardDrawn{nullptr};
};

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
    DrawResult drawCard();

    DrawData drawMultipleCards(int amount);

    /**
     * @brief Discards a card from the hand to the discard pile.
     *
     * @param handIndex Index of the card in the hand pile.
     * If index is out of bounds, no action is taken.
     */
    void discardFromHand(int handIndex);

    /// @brief Returns the number of cards currently in the hand.
    int getHandSize() const { return m_handPile.size(); }

    // bool isValidHandIndex(int index) const;

    /**
     * @brief Moves an exhausted/played card into the discard pile.
     *
     * This takes ownership of the CardInstance. If the pointer is null, no action is taken.
     *
     * @param exhaustedCard Owned card to discard.
     */
    void discard(std::unique_ptr<CardInstance> exhaustedCard);

    /**
     * @brief Removes a card from the hand and transfers ownership to the caller.
     *
     * This is how a card is played: the card is removed from the hand immediately
     * and returned as a std::unique_ptr for effect resolution.
     *
     * @param index Zero-based hand index.
     * @return Owned card if index is valid; nullptr otherwise.
     */
    std::unique_ptr<CardInstance> takeFromHand(int index);

    // /**
    //  * @brief Returns a reference to a card currently in hand.
    //  *
    //  * @warning No bounds checking is performed. Prefer getHandView() for read-only UI
    //  *          and takeFromHand() for safe ownership transfer.
    //  *
    //  * @param index Zero-based hand index.
    //  * @return Reference to the card at the given index.
    //  */
    // CardInstance& getCardInHand(int index) { return *m_handPile[index]; }

    /// @brief Returns a reference to the current hand pile.
    std::vector<std::unique_ptr<CardInstance>>& getHandPile() { return m_handPile; }

    /**
     * @brief Returns a non-owning view of the current hand for UI rendering.
     *
     * @return Vector of raw pointers to cards currently in hand.
     */
    std::vector<const CardInstance*> getHandView() const;

    void shuffle();

    void regenerateDeck();

  private:
    std::vector<std::unique_ptr<CardInstance>> m_drawPile;    ///< Draw pile (initial deck).
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
