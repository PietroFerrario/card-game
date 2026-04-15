#ifndef PLAYER_H
#define PLAYER_H

#include "deck/deckEntry.h"
#include "deck/deckPlayer.h"

#include "entity.h"

#include <string>
#include <string_view>
#include <vector>

/**
 * @brief Player-controlled entity with a persistent deck.
 *
 * Player represents the user-controlled character. In addition to the base
 * Entity combat state (HP, armor), it owns a persistent DeckPlayer used to
 * initialize combat decks for encounters.
 *
 * The Player object itself is long-lived across combats
 */
class Player : public Entity
{
  public:
    Player() {}
    /**
     * @brief Constructs a player with an initial deck and starting HP.
     *
     * @param startingCardList List of deck entries defining the player's deck.
     * @param hp Initial hit points for the player.
     */
    Player(const std::vector<DeckEntry>& startingCardList, int hp = 10);

    /// @brief Sets the display name of the player.
    void setName(std::string_view name) { m_name = name; }
    /// @brief Returns the display name of the player.
    std::string_view getName() const { return m_name; }

    /**
     * @brief Returns the player's persistent deck.
     *
     * This deck is used as the source for constructing DeckCombat instances at the start of combat
     * encounters.
     *
     */
    const DeckPlayer& getDeckPlayer() const { return m_deckPlayer; }

    /**
     * @brief Returns the player's persistent deck.
     *
     * This deck is used as the source for constructing DeckCombat instances at the start of combat
     * encounters.
     *
     */
    DeckPlayer& getDeckPlayer() { return m_deckPlayer; }

  private:
    DeckPlayer m_deckPlayer;
};

#endif