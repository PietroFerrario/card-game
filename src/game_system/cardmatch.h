

#ifndef CARDMATCH_H
#define CARDMATCH_H

#include "combat/combatSystem.h"
#include "deck/deckCombat.h"
#include "entities/enemies/enemy.h"
#include "entities/player.h"
#include "factories/cardFactory.h"

class Player;
class Enemy;

/**
 * @brief Orchestrates a single combat encounter between a player and an enemy.
 *
 * CardMatch coordinates the combat flow at a high level:
 * - drawing cards into the player's hand,
 * - playing a card from the hand,
 * - resolving the card's effects,
 * - updating player/enemy combat state (e.g., armor).
 *
 * CardMatch does not own the Player or Enemy instances; it stores references to
 * objects managed elsewhere.
 */

class CardMatch
{

  public:
    /**
     * @brief Construct a new Card Match object.
     *
     * @param player Player partecipating in the encounter (must outlive the CardMatch).
     * @param enemy Enemy partecipating in the encounter (must outlive the CardMatch).
     */
    CardMatch(Player& player, Enemy& enemy);

    /**
     * @brief Draws multiple cards: moves cards from the combat deck into the player's hand.
     *
     * Drawing behaviour (empty deck handling) delegated to DeckCombat.
     *
     * @param amount Number of cards to draw. Non-positive: no action.
     *
     *
     */
    void drawMultipleCards(int amount);

    /**
     * @brief Plays a card from the hand and resolves all its effects.
     *
     * If empty hand or invalid index: no action. (logs in debug, temporary).
     * Effects are applied in the order defined by the card's CardDefinition.
     *
     * @param handIndex Index of the card in the handPile.
     *

     */
    void playCard(int handIndex);

    /**
     * @brief Grants armor to the player
     *
     * Typically triggered b an effect defined in a CardDefinition.
     * The amount of armor granted is specified by the Card's armor value.
     *
     * @param defense Defense amount of armor to add.
     */
    void gainArmor(int defense);

  private:
    Player& m_player; ///< Non-owning reference to the player in the encounter.
    Enemy& m_enemy;   ///< Non-owning reference to the enemy in the encounter.

    CardFactory m_cardFactory; ///< Populate the CombatDeck with CardInstances.

    DeckCombat m_deckCombat; ///< Manage draw/discard/piles during combat.

    CombatSystem m_combatSystem;
};

#endif