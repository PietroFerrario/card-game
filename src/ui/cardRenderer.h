#ifndef CARDRENDERER_H
#define CARDRENDERER_H

#include <memory>
#include <string>
#include <string_view>
#include <vector>

class CardInstance;

enum class SlotAlignment
{
    Left,
    Center,
    Right
};

struct Slot
{
    int rowIndex;
    int columnIndex;
    int maxWidth;
    SlotAlignment alignment;
};

class CardRenderer
{
  public:
    CardRenderer(const CardInstance& currentCard);

    std::vector<std::string> renderCard();
    std::string fitText(Slot currentSlot, std::string_view text);

  private:
    const CardInstance& m_cardToRender;

    const int m_width{24};
    const int m_height{8};

    const char m_padding{' '};
    const char m_verticalBorder{'|'};
    const char m_horizontalBorder{'—'};

    Slot m_firstName{2, 5, 14, SlotAlignment::Center};
    Slot m_secondName{3, 5, 8, SlotAlignment::Center};
    Slot m_damage{5, 2, 8, SlotAlignment::Left};
    Slot m_armor{5, 16, 6, SlotAlignment::Right};
    Slot m_effectsSum{7, 3, 18, SlotAlignment::Center};
};

#endif // CARDRENDERER_H