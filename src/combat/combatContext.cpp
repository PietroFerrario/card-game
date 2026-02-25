#include "combatContext.h"
#include "combat/combatEvents.h"
#include "combatSystem.h"
#include "deck/deckCombat.h"
#include "entities/entity.h"
#include "game_system/matchData.h"
#include "util/debug.h"

#include <utility>

CombatContext::CombatContext(CombatSystem& combatSystem, Entity& actor, Entity& opponent,
                             DeckCombat& deckCombat, TurnData& turnData)
    : m_combatSystem{combatSystem}, m_actor{actor}, m_opponent{opponent}, m_deckCombat{deckCombat},
      m_turnData{turnData}
{
    m_effectMessage = nullptr;
}

CombatContext::EffectMessageScope::EffectMessageScope(CombatContext& combatContext,
                                                      std::vector<std::string>& effectMessage)
    : m_combatContext{combatContext}
{
    m_combatContext.m_effectMessage = &effectMessage;
}

CombatContext::EffectMessageScope::~EffectMessageScope()
{
    m_combatContext.m_effectMessage = nullptr;
}

void CombatContext::setEffectMessage(std::vector<std::string>* effectMessage)
{
    m_effectMessage = effectMessage;
}

void CombatContext::resetEffectMessage() { m_effectMessage = nullptr; }

Entity& CombatContext::resolveTarget(Target target)
{
    switch (target)
    {
    case Target::Self:
    {
        // DEBUG_LOG("Selected Self");
        return m_actor;
    }
    case Target::Opponent:
    {
        // DEBUG_LOG("Selected Opponent");
        return m_opponent;
    }
    default:
    {
        DEBUG_LOG("No valid target selected. Crashing");
        std::unreachable();
    }
    }
    std::unreachable();
}

const Entity& CombatContext::resolveTarget(Target target) const
{
    switch (target)
    {
    case Target::Self:
    {
        // DEBUG_LOG("Selected Self");
        return m_actor;
    }
    case Target::Opponent:
    {
        // DEBUG_LOG("Selected Opponent");
        return m_opponent;
    }
    default:
    {
        DEBUG_LOG("No valid target selected. Crashing");
        std::unreachable();
    }
    }
    std::unreachable();
}

std::string CombatContext::messageTarget(Target target) const
{

    if (target != Target::Self)
    {
        return std::string(resolveTarget(target).getName()) + " ";
    }
    else
        return "";
}

void CombatContext::gainArmor(Target target, int amount)
{
    m_combatSystem.gainArmor(resolveTarget(target), amount);
    if (m_effectMessage)
    {
        m_effectMessage->emplace_back(std::format("{}Armor: +{}", messageTarget(target), amount));
    }
}

void CombatContext::gainAttack(Target target, int amount)
{
    m_combatSystem.gainAttack(resolveTarget(target), amount);
    if (m_effectMessage)
    {
        m_effectMessage->emplace_back(std::format("{}Attack: +{}", messageTarget(target), amount));
    }
}

DamageResult CombatContext::dealDamage(Target target, int amount, bool ignoreArmor)
{
    return m_combatSystem.dealDamage(resolveTarget(target), amount, ignoreArmor);
}

void CombatContext::drawMultipleCardFromEffect(int amount)
{
    std::string drawMessage;
    m_drawData = m_deckCombat.drawMultipleCards(amount);

    DEBUG_LOG("Drawing cards completed.");

    if (m_effectMessage)
    {
        m_effectMessage->emplace_back(std::format("Drawing: {}", amount));
    }
}

std::optional<DrawData> CombatContext::getDrawData()
{
    std::optional<DrawData> result{std::move(m_drawData)};
    m_drawData.reset();
    return result;
}

void CombatContext::gainActions(int amount)
{
    m_turnData.playerRemainingActions += amount;
    if (m_effectMessage)
    {
        m_effectMessage->emplace_back(std::format("Actions: +{}", amount));
    }
}

// FOR THE FUTURE: Effect summaries are currently collected as strings for simplicity.
// A refactor may replace this with structured effect events
// (similar to DrawData) to improve aggregation and rendering flexibility.