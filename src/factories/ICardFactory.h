#ifndef ICARDFACTORY_H
#define ICARDFACTORY_H

#include <memory>
#include <string>

class CardDefinition;
class CardInstance;

class ICardFactory
{
public:
    virtual std::unique_ptr<CardInstance> makeSingleCard(const std::string &cardId) const = 0;

    virtual ~ICardFactory() = default;
};

#endif // CARDFACTORY_H