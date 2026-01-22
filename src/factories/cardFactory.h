#ifndef CARDFACTORY_H
#define CARDFACTORY_H

#include "ICardFactory.h"

#include <string_view>
#include <unordered_map>

class CardDefinition;
class CardInstance;

class CardFactory : public ICardFactory
{
public:
    CardFactory();

    void registerDefinition(std::string_view cardId, std::unique_ptr<CardDefinition> uniqueCardDefinition);

    void registerCards();

    std::unique_ptr<CardInstance> makeSingleCard(const std::string &cardId) const override;

    ~CardFactory();

private:
    std::unordered_map<std::string, std::unique_ptr<CardDefinition>> m_cardMap;
};

#endif // CARDFACTORY_H