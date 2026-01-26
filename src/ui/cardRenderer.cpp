#include "cardRenderer.h"
#include "cards/cardInstance.h"

#include <cassert>
#include <iostream>

CardRenderer::CardRenderer(const CardInstance& currentCard) : m_cardToRender{currentCard} {}

std::vector<std::string> CardRenderer::renderCard() { std::vector<std::string> grid; }

std::string CardRenderer::fitText(Slot slot, std::string_view text)
{
    assert((slot.rowIndex > 0 && slot.rowIndex <= m_width) && "Invalid row index");
    assert((slot.columnIndex > 0 && slot.columnIndex <= m_height) && "Invalid column index");
    assert(slot.columnIndex + slot.maxWidth <= m_width && "Slot too large");

    int textLength = text.length();

    if (textLength > slot.maxWidth)
    {
        text.remove_suffix(textLength - slot.maxWidth);
        return std::string{text};
    }
    else if (textLength < slot.maxWidth)
    {
        std::string s{text};
        switch (slot.alignment)
        {
        case (SlotAlignment::Left):
        {
            s.insert(s.size(), slot.maxWidth - textLength, ' ');
        }
        case (SlotAlignment::Right):
        {
            s.insert(0, slot.maxWidth - textLength, ' ');
        }
        case (SlotAlignment::Center):
        {
            s.insert(0, (slot.maxWidth - textLength) / 2, ' ');
            s.insert(s.size(), (slot.maxWidth - textLength) / 2, ' ');
        }
        }
    }
}