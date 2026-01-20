#ifndef CARDFACTORY_H
#define CARDFACTORY_H

#include <vector>
#include <string_view>
#include <memory>
#include <unordered_map>

class CardDefinition;
class Card;
struct DeckEntry;

class CardFactory
{
public:
    CardFactory();

    void registerDefinition(std::string_view cardId, std::unique_ptr<CardDefinition> uniqueCardDefinition);

    void registerCards();

    std::unique_ptr<Card> makeSingleCard(const std::string &cardId);

    ~CardFactory();

private:
    std::unordered_map<std::string, std::unique_ptr<CardDefinition>> m_cardMap;
};

#endif // CARDFACTORY_H