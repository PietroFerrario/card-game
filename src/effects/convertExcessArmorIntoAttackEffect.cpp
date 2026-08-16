#include "convertExcessArmorIntoAttackEffect.h"
#include "combat/combatContext.h"
#include "entities/entity.h"
#include "util/debug.h"

void ConvertExcessArmorIntoAttackEffect::resolve(CombatContext& combatContext,
                                                 const CardParams& values)
{
    combatContext.changeArmorPolicy(m_target, Entity::EndOfTurnArmorPolicy::ConvertToAttack);
    DEBUG_LOG("Applied effect ConvertExcessArmorIntoAttack");
}
