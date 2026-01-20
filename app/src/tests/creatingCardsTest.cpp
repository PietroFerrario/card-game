#include "cards/cardInstance.h"
#include "factories/cardFactory.h"

#include <memory>

int main()
{
    const CardFactory factory;
    std::unique_ptr<CardInstance> shieldWarrior = factory.makeSingleCard("shieldWarrior");

    return 0;
}