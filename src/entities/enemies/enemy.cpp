#include "enemy.h"
#include <cassert>
#include <utility>

Enemy::Enemy(std::string_view name, int hp, std::vector<EnemyMove> moves)
    : Entity{hp, name}, m_moves{std::move(moves)}
{
}

const EnemyMove& Enemy::nextMove()
{
    assert(!(m_moves.empty()) && "Calling an EnemyMove on an enemy without valid EnemyMoves");

    const EnemyMove& move = m_moves[m_moveIndex];

    m_moveIndex = (m_moveIndex + 1) % m_moves.size();

    return move;
}
