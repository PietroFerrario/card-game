#include "wolfPack.h"
#include "combat/combatTarget.h"
#include "effects/gainArmorEffect.h"

WolfPack::WolfPack(int hp) : Enemy{hp}
{
    m_name = "Pack of Wolves";

    m_moves.emplace_back();
    EnemyMove& move = m_moves.back();

    move.effectList.emplace_back(std::make_unique<GainArmorEffect>(Target::Self));
    move.effectParams.damage = 5;
    move.effectParams.armor = 5;
    move.name = "Pack Tactics";
}