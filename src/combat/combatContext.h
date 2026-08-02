#ifndef COMBATCONTEXT_H
#define COMBATCONTEXT_H

#include "combatTarget.h"
#include "deck/drawData.h"

#include <optional>
#include <string>
#include <string_view>
#include <vector>

class CombatSystem;
class Entity;
class DeckCombat;
class Enemy;
struct TurnData;
struct DamageResult;

/**
 * @brief Execution context for resolving combat effects.
 *
 * CombatContext binds an actor/opponent relationship for the current action and
 * provides a narrow set of combat operations that effects may invoke.
 *
 * Effects target using logical selectors (Target::Self / Target::Opponent).
 * CombatContext resolves these selectors to Entity references and forwards
 * requests to CombatSystem, which owns the combat rules.
 *
 * CombatContext does not own any objects; it stores references that must outlive it.
 */
class CombatContext
{
  public:
    /**
     * @brief Constructs a context for effect resolution.
     *
     * @param combatSystem Combat rules engine used to apply mutations.
     * @param actor Entity performing the current action (Target::Self).
     * @param opponent Entity opposing the actor (Target::Opponent).
     */
    CombatContext(CombatSystem& combatSystem, Entity& actor, Entity& opponent,
                  DeckCombat& deckCombat, TurnData& turnData, Enemy* enemy = nullptr);

    void setEffectMessage(std::vector<std::string>* effectMessage);
    void resetEffectMessage();

    /**
     * @brief Grants armor to the selected logical target.
     *
     * Resolves the target (self/opponent) and forwards the operation to CombatSystem.
     *
     * @param target Logical target selector.
     * @param amount Armor amount to add.
     */
    void gainArmor(Target target, int amount);

    /**
     * @brief Grants attack to the selected logical target.
     *
     * Resolves the target (self/opponent) and forwards the operation to CombatSystem.
     *
     * @param target Logical target selector.
     * @param amount Attack amount to add.
     */
    void gainAttack(Target target, int amount);

    DamageResult dealDamage(Target target, int amount, bool ignoreArmor = false);

    void drawMultipleCardFromEffect(int amount);

    std::optional<DrawData> getDrawData();

    void gainActions(int amount);

    const DeckCombat& getDeckCombatView() const { return m_deckCombat; }

    // Card effects

    void maintainPlayerArmor();
    void avoidPlayerDeath();

    // Enemy effects

    void limitCardToPlay(int amount);
    void takeCardHostage();
    void increaseDamageEnemyMove(std::string_view enemyMoveName, int amount);
    void addCardToDeck(std::string_view cardId, int amount);
    void maintainEnemyArmor();

    class EffectMessageScope
    {
      public:
        EffectMessageScope(CombatContext& combatContext, std::vector<std::string>& effectMessage);
        ~EffectMessageScope();

        EffectMessageScope(const EffectMessageScope&) = delete;
        EffectMessageScope& operator=(const EffectMessageScope&) = delete;
        EffectMessageScope(EffectMessageScope&&) = delete;
        EffectMessageScope& operator=(EffectMessageScope&&) = delete;

      private:
        CombatContext& m_combatContext;
    };

  private:
    CombatSystem& m_combatSystem;
    Entity& m_actor;
    Entity& m_opponent;

    DeckCombat& m_deckCombat;
    TurnData& m_turnData;
    std::optional<DrawData> m_drawData;

    std::vector<std::string>* m_effectMessage;
    Enemy* m_enemy;

    /**
     * @brief Resolves a logical Target to the corresponding Entity in this context.
     *
     * @param target Logical target selector.
     * @return Reference to the resolved Entity (actor or opponent).
     */
    Entity& resolveTarget(Target target);
    const Entity& resolveTarget(Target target) const;

    std::string messageTarget(Target target) const;
};

#endif // COMBATCONTEXT_H
