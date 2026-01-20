#ifndef CARDMAKER_H
#define CARDMAKER_H

#include <vector>
#include <string_view>
#include <memory>
#include <unordered_map>

class CardDefinition;
class Card;

class CardMaker
{
public:
    CardMaker();

    void registerDefinition(std::string_view cardId, std::unique_ptr<CardDefinition> uniqueCardDefinition);

    void registerCards();

    Card makeSingleCard(const std::string &cardId);

private:
    std::unordered_map<std::string, std::unique_ptr<CardDefinition>> m_cardMap;
};

#endif // CARDMAKER_H