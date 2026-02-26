#include "bandits.h"
#include "combat/combatTarget.h"
#include "effects/gainArmorEffect.h"
#include "effects/gainAttackEffect.h"
#include "effects/limitCardToPlayEffect.h"

Bandits::Bandits(int hp) : Enemy{hp}
{
    m_name = "Bandits";

    m_moves.emplace_back();
    EnemyMove& basicAttack = m_moves.back();
    basicAttack.effectList.emplace_back(std::make_unique<GainAttackEffect>(Target::Self));
    basicAttack.effectParams.damage = 5;
    basicAttack.name = "Uncoordinated Attack";

    m_moves.emplace_back();
    EnemyMove& ambush = m_moves.back();
    ambush.effectList.emplace_back(std::make_unique<GainArmorEffect>(Target::Self));
    ambush.effectList.emplace_back(std::make_unique<LimitCardToPlayEffect>());
    ambush.effectParams.armor = 6;
    ambush.effectParams.cardsLimit = 2;
    ambush.name = "Ambush!!!";
}