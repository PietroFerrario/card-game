#ifndef DECKCOMBAT_H
#define DECKCOMBAT_H

#include <memory>
#include <string>
#include <vector>

class DeckPlayer;
class DeckEntry;
class CardInstance;
class ICardFactory;

class DeckCombat
{
  public:
    DeckCombat(const DeckPlayer& deck_player, const ICardFactory& factory);

    void drawCard();

  private:
    std::vector<std::unique_ptr<CardInstance>> m_cards;
    std::vector<std::unique_ptr<CardInstance>> m_handPile;
    std::vector<std::unique_ptr<CardInstance>> m_discardPile;

    const ICardFactory& m_factory;

    void populateDeck(const std::vector<DeckEntry>& cardList);
};

#endif // DECKCOMBAT_H
