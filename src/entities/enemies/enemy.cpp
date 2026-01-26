#include "enemy.h"
#include <utility>

Enemy::Enemy(int hp) : Entity{hp} {}

const EnemyMove& Enemy::nextMove()
{
    if (m_moves.size() == 0)
    {
        std::unreachable();
    }
    if (m_moveIndex < 0 || m_moveIndex >= static_cast<int>(m_moves.size()))
    {
        m_moveIndex = 0;
        return m_moves[m_moveIndex];
    }
    ++m_moveIndex;
    return m_moves[m_moveIndex];
}

void Enemy::advanceMoves()
{
    int numberOfMoves = static_cast<int>(m_moves.size());
    if (numberOfMoves == 0)
    {
        return;
    }
    ++m_moveIndex;
    if (m_moveIndex >= numberOfMoves)
    {
        m_moveIndex = 0;
    }
}