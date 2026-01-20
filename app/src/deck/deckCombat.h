#ifndef DECKCOMBAT_H
#define DECKCOMBAT_H

#include <vector>
#include <string>
#include <memory>

class DeckPlayer;
class DeckEntry;
class CardInstance;
class ICardFactory;

class DeckCombat
{
public:
    DeckCombat(const DeckPlayer &deck_player, const ICardFactory &factory);

    void populateDeck(const std::vector<DeckEntry> &cardList);

private:
    std::vector<std::unique_ptr<CardInstance>> m_cards;

    const ICardFactory &m_factory;
};

#endif // DECKCOMBAT_H
