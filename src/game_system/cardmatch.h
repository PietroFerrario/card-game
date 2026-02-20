

#ifndef CARDMATCH_H
#define CARDMATCH_H

#include "matchData.h"

#include "combat/combatSystem.h"
#include "deck/deckCombat.h"
#include "entities/enemies/enemy.h"
#include "entities/player.h"
#include "factories/cardFactory.h"
#include "ui/IMatchView.h"

class Player;
class Enemy;

/**
 * @brief Orchestrates a single combat encounter between one player and one enemy.
 *
 * CardMatch coordinates encounter-level flow:
 * - builds a combat deck from the player's persistent deck (DeckCombat + CardFactory)
 * - draws cards into the player's hand
 * - resolves a played card by executing its ordered Effect list
 * - runs the enemy turn by resolving the next EnemyMove
 *
 * CardMatch owns the runtime combat deck (DeckCombat) and the rules engine (CombatSystem).
 * Player and Enemy objects are referenced and must outlive the CardMatch.
 *
 * Effect resolution is performed using CombatContext, which routes effect requests to
 * CombatSystem. See @ref combat_effect_pipeline for the full resolution flow.
 */
class CardMatch
{

  public:
    /**
     * @brief Constructs a match for the given player and enemy.
     *
     * Builds a fresh DeckCombat from the player's persistent deck.
     *
     * @param player Player participating in the encounter (must outlive the CardMatch).
     * @param enemy Enemy participating in the encounter (must outlive the CardMatch).
     */
    CardMatch(IMatchView& matchView, Player& player, Enemy& enemy);

    /**
     * @brief Draws multiple cards into the player's hand.
     *
     * Delegates empty-deck behavior to DeckCombat.
     *
     * @param amount Number of cards to draw. If amount <= 0, no action is taken.
     */
    void drawMultipleCards(int amount);

    /**
     * @brief Plays a card from the hand and resolves all of its effects.
     *
     * The selected card is removed from the hand immediately via DeckCombat::takeFromHand()
     * Effects are then resolved in the order defined by the card's CardDefinition. After
     * resolution, the card is moved to the discard pile.
     *
     * If the hand index is invalid, no action is taken.
     *
     * @param handIndex Zero-based index of the card in the hand.
     */
    void playCard(int handIndex);

    /**
     * @brief Legacy helper that directly increases the player's armor.
     *
     * @warning This bypasses CombatSystem and exists only for older code paths.
     *          Current effects should grant armor via CombatContext/CombatSystem.
     */
    void gainArmor(int defense);

    void spendAction(TurnData& turnData);
    void reduceAction(TurnData& turnData, int amount);

    void turnLoop();

    void playerTurn(TurnData& currentTurnData);

    bool canPlayerAct(TurnData& currentTurnData);

    /**
     * @brief Executes the enemy's next move and resolves its effects.
     *
     * The enemy provides an EnemyMove via Enemy::nextMove(). Effects are resolved in order
     * using a CombatContext where the enemy is the actor and the player is the opponent.
     */
    void enemyTurn();

  private:
    IMatchView& m_matchView;

    Player& m_player; ///< Non-owning reference to the player in the encounter.
    Enemy& m_enemy;   ///< Non-owning reference to the enemy in the encounter.

    CardFactory m_cardFactory; ///< Populate the CombatDeck with CardInstances.

    DeckCombat m_deckCombat; ///< Manage draw/discard/piles during combat.

    CombatSystem m_combatSystem; ///< Applies combat rules and state mutation.

    MatchData m_matchData;
};

#endif