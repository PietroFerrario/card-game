#include "bandits.h"
#include "combat/combatTarget.h"
#include "effects/gainArmorEffect.h"
#include "effects/gainAttackEffect.h"
#include "effects/hostageCardEffect.h"
#include "effects/limitCardToPlayEffect.h"

Bandits::Bandits(int hp) : Enemy{hp}
{
    m_name = "Ragged Bandits";
    m_id = EnemyId::Bandits;

    m_moves.emplace_back();
    EnemyMove& ambush = m_moves.back();
    ambush.effectList.emplace_back(std::make_unique<GainArmorEffect>(Target::Self));
    ambush.effectList.emplace_back(std::make_unique<LimitCardToPlayEffect>());
    ambush.effectParams.armor = 6;
    ambush.effectParams.cardsLimit = 4;
    ambush.name = "Ambush!!!";
    ambush.description = "They caught you by surprise!";

    m_moves.emplace_back();
    EnemyMove& basicAttack = m_moves.back();
    basicAttack.effectList.emplace_back(std::make_unique<GainAttackEffect>(Target::Self));
    basicAttack.effectParams.damage = 5;
    basicAttack.name = "Uncoordinated Attack";
    basicAttack.description = "No tactics or discipline, the ragged band leaps at you!";

    m_moves.emplace_back();
    EnemyMove& hostage = m_moves.back();
    hostage.effectList.emplace_back(std::make_unique<HostageCardEffect>());
    hostage.name = "Hostage";
    hostage.description = "A hidden member of the gang came out from nowhere and now he's holding "
                          "a knife to your comrade throat.";
}