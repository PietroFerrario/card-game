#include "wolfPack.h"
#include "combat/combatTarget.h"
#include "effects/gainArmorEffect.h"

WolfPack::WolfPack(int hp = 30) : Enemy{hp}
{
    EnemyMove packTactics;
    packTactics.effectList.emplace_back(std::make_unique<GainArmorEffect>(Target::Self));
    packTactics.effectParams = {5, 5};
    packTactics.name = "Pack Tactics";

    m_moves.push_back(packTactics);
}