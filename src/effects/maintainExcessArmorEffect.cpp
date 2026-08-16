#include "maintainExcessArmorEffect.h"
#include "combat/combatContext.h"
#include "entities/entity.h"
#include "util/debug.h"

void MaintainExcessArmorEffect::resolve(CombatContext& combatContext, const CardParams& values)
{
    combatContext.changeArmorPolicy(m_target, Entity::EndOfTurnArmorPolicy::Maintain);
    DEBUG_LOG("Applied effect MaintainEccessArmor");
}
