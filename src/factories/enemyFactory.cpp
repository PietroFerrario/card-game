#include "enemyFactory.h"
#include "entities/enemies/bandits.h"

std::unique_ptr<Enemy> EnemyFactory::makeEnemy(EnemyId id)
{
    switch (id)
    {
    case (EnemyId::Bandits):
    {
        return std::make_unique<Bandits>();
    }

    default:
        return nullptr;
        break;
    }
}