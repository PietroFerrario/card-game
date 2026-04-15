#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include "entities/enemies/enemy.h"
#include "entities/enemies/enemyId.h"
#include <memory>

namespace EnemyFactory
{
std::unique_ptr<Enemy> makeEnemy(EnemyId id);

} // namespace EnemyFactory

#endif // ENEMYFACTORY_H