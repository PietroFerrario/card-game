#ifndef ENEMYMOVE_H
#define ENEMYMOVE_H

#include "effects/effect.h"
#include "effects/effectParams.h"
#include <memory>
#include <string>
#include <vector>

struct EnemyMove
{
    std::vector<std::unique_ptr<Effect>> effectList{};
    EffectParams effectParams;
    std::string name;
};

#endif // ENEMYMOVE_H