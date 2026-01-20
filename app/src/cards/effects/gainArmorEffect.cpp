#include "gainArmorEffect.h"
#include "cards/cardInstance.h"
#include "game_system/cardmatch.h"

void GainArmorEffect::apply(CardMatch &card_match, CardInstance &card)
{
    card_match.gainArmor(card.getArmor());
}