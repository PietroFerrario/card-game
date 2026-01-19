#include "gainBlockEffect.h"
#include "../card.h"
#include "game_system/cardmatch.h"

void GainBlockEffect::apply(CardMatch &card_match, Card &card)
{
    card_match.gainArmor(card.get_def());
}