#ifndef ENEMY_H
#define ENEMY_H

#include "enemyMove.h"
#include "entities/entity.h"

#include <vector>

/**
 * @brief Base class for enemies with a predefined move sequence.
 *
 * Enemy represents a non-player combat entity whose behavior is defined by
 * an ordered list of EnemyMove objects.
 *
 * Each call to nextMove() returns the current move and advances the internal
 * move index, typically cycling through the sequence.
 *
 * Enemy does not execute its moves directly; orchestration and effect
 * resolution are handled externally (e.g., by CardMatch).
 */
class Enemy : public Entity
{
  public:
    /**
     * @brief Returns the next move in the enemy's move sequence.
     *
     * The move index is advanced after each call. The sequence is treated as cyclic.
     *
     * @return Reference to the selected EnemyMove.
     *
     * @pre The enemy must define at least one EnemyMove.
     */
    const EnemyMove& nextMove();

  protected:
    /**
     * @brief Constructs an enemy with the given starting HP.
     *
     * @param hp Initial hit points for the enemy.
     */
    Enemy(int hp);
    std::vector<EnemyMove> m_moves{};
    int m_moveIndex{0};
};

#endif // ENEMY_H