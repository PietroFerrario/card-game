#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include "effectFactory.h"
#include "entities/enemies/enemy.h"
#include "entities/enemies/enemyData.h"
#include <memory>
#include <unordered_map>

class EnemyFactory
{
  public:
    EnemyFactory(std::unordered_map<std::string, EnemyData> enemyMap);

    std::unique_ptr<Enemy> makeEnemy(std::string enemyId);

  private:
    EffectFactory m_effectFactory;
    std::unordered_map<std::string, EnemyData> m_enemyMap;
};

#endif // ENEMYFACTORY_H
