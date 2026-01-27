#ifndef CARDRENDERER_H
#define CARDRENDERER_H

#include <memory>
#include <optional>
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

struct NameLayout
{
    std::string firstName;
    std::optional<std::string> secondName;
};

class CardRenderer
{
  public:
    CardRenderer() = default;

    std::vector<std::string> renderCard(const CardInstance& cardToRender);

  private:
    void drawTemplate(std::vector<std::string>& grid);
    std::string fitText(Slot currentSlot, std::string_view text);
    void writeSlot(std::vector<std::string>& grid, Slot slot, std::string_view formattedText);
    static void appendWord(std::string& line, std::string_view word);
    NameLayout drawLayout(std::string_view cardName, Slot currentSlot);

    const int m_width{24};
    const int m_height{12};

    const int m_nameWidth{10};
    const int m_nameColumn{m_width / 2 - m_nameWidth / 2};

    const char m_padding{' '};
    const char m_verticalBorder{'|'};
    const char m_horizontalBorder{'-'};

    Slot m_firstNameSlot{1, m_nameColumn, m_nameWidth, SlotAlignment::Center};
    Slot m_secondNameSlot{2, m_nameColumn, m_nameWidth, SlotAlignment::Center};

    Slot m_atkLabelSlot{5, 2, 6, SlotAlignment::Left};
    Slot m_defLabelSlot{5, m_width - 10, 6, SlotAlignment::Left};

    Slot m_damageValueSlot{5, 8, 2, SlotAlignment::Right};
    Slot m_armorValueSlot{5, m_width - 4, 2, SlotAlignment::Right};
    Slot m_effectsSumSlot{7, 3, 18, SlotAlignment::Center};
    Slot m_firstDescrSlot{8, 2, m_width - 4, SlotAlignment::Left};
    Slot m_secondDescrSlot{9, 2, m_width - 4, SlotAlignment::Left};
};

#endif // CARDRENDERER_H