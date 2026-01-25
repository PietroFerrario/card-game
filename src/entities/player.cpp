#include "player.h"

Player::Player(const std::vector<DeckEntry>& startingCardList, int hp)
    : Entity{hp}, m_deckPlayer{startingCardList}
{
}
