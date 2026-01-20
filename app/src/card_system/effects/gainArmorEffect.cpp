#include "gainArmorEffect.h"
#include "../card.h"
#include "game_system/cardmatch.h"

void GainArmorEffect::apply(CardMatch &card_match, Card &card)
{
    card_match.gainArmor(card.getArmor());
}