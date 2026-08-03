#include "combatContext.h"
#include "cards/cardDefinition.h"
#include "cards/cardInstance.h"
#include "combat/combatEvents.h"
#include "combatSystem.h"
#include "deck/deckCombat.h"
#include "entities/enemies/enemy.h"
#include "entities/entity.h"
#include "entities/player.h"
#include "game_system/matchData.h"
#include "util/Random.h"

#include "util/debug.h"

#include <algorithm>
#include <utility>

CombatContext::CombatContext(CombatSystem& combatSystem, Entity& actor, Entity& opponent,
                             DeckCombat& deckCombat, TurnData& turnData, const Player& player,
                             Enemy* enemy)
    : m_combatSystem{combatSystem}, m_actor{actor}, m_opponent{opponent}, m_deckCombat{deckCombat},
      m_turnData{turnData}, m_player{player}, m_enemy{enemy}
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

void CombatContext::limitCardToPlay(int amount)
{
    auto& limit = m_turnData.cardsToPlayLimit;

    if (limit.has_value())
    {
        limit.value() = std::min(limit.value(), amount);
    }
    else
    {
        limit = amount;
    }
    if (m_effectMessage)
    {
        m_effectMessage->emplace_back(std::format("Max cards to play: {}", limit.value()));
    }
}

void CombatContext::maintainPlayerArmor() { m_turnData.maintainPlayerArmorFlag = true; }
void CombatContext::maintainEnemyArmor() { m_turnData.maintainEnemyArmorFlag = true; }

int CombatContext::getPlayerPopulation() { return m_player.getPopulation(); }

void CombatContext::avoidPlayerDeath() { m_turnData.avoidDeathFlag = true; }

void CombatContext::takeCardHostage()
{
    int handSize = m_deckCombat.getHandSize();
    if (handSize > 0)
    {
        std::unique_ptr<CardInstance> cardTakenHostage =
            m_deckCombat.takeFromHand(Random::get(0, handSize - 1));

        if (m_effectMessage && cardTakenHostage)
        {
            m_effectMessage->emplace_back(std::format(
                "Card taken hostage: {}", cardTakenHostage->getCardDefinition().getName()));
        }
    }
}

void CombatContext::addCardToDeck(std::string_view cardId, int amount)
{
    DeckEntry card{static_cast<std::string>(cardId), CardParams{}};

    for (int i{0}; i < amount; i++)
    {
        m_deckCombat.addCardToCombatDeck(card);
    }

    if (m_effectMessage)
    {
        m_effectMessage->emplace_back(
            std::format("{} {} cards added to your deck.", amount, cardId));
    }

    m_deckCombat.shuffle();
}

void CombatContext::increaseDamageEnemyMove(std::string_view enemyMoveName, int amount)
{

    if (!m_enemy)
    {
        DEBUG_LOG("ModifyEnemyMove called with no enemy in context");
        return;
    }

    auto& moveList{m_enemy->getEnemyMovesList()};

    auto foundMove =
        std::find_if(moveList.begin(), moveList.end(),
                     [enemyMoveName](const EnemyMove& move) { return move.name == enemyMoveName; });

    if (foundMove == moveList.end())
    {
        DEBUG_LOG("No enemy move name " << enemyMoveName << "in enemy " << m_enemy->getName());
        return;
    }

    foundMove->effectParams.damage += amount;

    if (m_effectMessage)
    {
        m_effectMessage->emplace_back(
            std::format("{} damage on next turn: +{}", foundMove->name, amount));
    }
}

// FOR THE FUTURE: Effect summaries are currently collected as strings for simplicity.
// A refactor may replace this with structured effect events
// (similar to DrawData) to improve aggregation and rendering flexibility.
