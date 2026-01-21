#include "gainArmorEffect.h"
#include "cards/cardDefinition.h"
#include "cards/cardInstance.h"
#include "game_system/cardmatch.h"
#include "util/debug.h"

void GainArmorEffect::apply(CardMatch& card_match, CardInstance& card)
{
    card_match.gainArmor(card.getArmor());
    DEBUG_LOG("Applied effect GainArmor from card: " << card.getCardDefinition().getID());
}