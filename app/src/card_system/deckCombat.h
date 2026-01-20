#ifndef DECKCOMBAT_H
#define DECKCOMBAT_H

#include <vector>
#include <string>
#include <memory>

class DeckPlayer;
class CardInstance;
class CardMaker;

class DeckCombat
{
public:
    DeckCombat(const DeckPlayer &deck_player);

    void DeckCombat::populateDeck(const std::vector<DeckEntry> &cardList);

private:
    std::vector<std::unique_ptr<CardInstance>> m_cards;

    CardMaker &m_cardMaker;
};

#endif // DECKCOMBAT_H
