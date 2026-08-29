#include "nodeRenderer.h"
#include "game_events/eventNode.h"
#include "textWrap.h"

#include <cassert>
#include <format>

std::vector<std::string> NodeRenderer::renderNode(const EventNode& nodeToRender) const
{
    std::vector<std::string> grid(m_height, std::string(m_width, ' '));

    drawTemplate(grid);

    writeSlot(grid, m_layerSlot, fitText(m_layerSlot, std::format("Stage {}", nodeToRender.layer)));

    const std::vector<std::string> description{
            wrapText(nodeToRender.previewDescription, m_descriptionSlots.front().maxWidth)};

    for (size_t i{0}; i < description.size() && i < m_descriptionSlots.size(); ++i)
    {
        writeSlot(grid, m_descriptionSlots.at(i),
                  fitText(m_descriptionSlots.at(i), description.at(i)));
    }

    return grid;
}

void NodeRenderer::drawTemplate(std::vector<std::string>& grid) const
{
    grid.at(0).assign(m_width, m_horizontalBorder);
    grid.at(m_height - 1).assign(m_width, m_horizontalBorder);

    for (int i{1}; i < m_height - 1; ++i)
    {
        grid.at(i).replace(0, 1, 1, m_verticalBorder);
        grid.at(i).replace(m_width - 1, 1, 1, m_verticalBorder);
    }

    // separator under the stage line
    grid.at(2).replace(1, m_width - 2, m_width - 2, m_horizontalBorder);
}

std::string NodeRenderer::fitText(Slot slot, std::string_view text) const
{
    int textLength = static_cast<int>(text.length());
    std::string s{text};

    if (textLength > slot.maxWidth)
    {
        text.remove_suffix(textLength - slot.maxWidth);
        s = text;
    }
    else if (textLength < slot.maxWidth)
    {
        switch (slot.alignment)
        {
        case (SlotAlignment::Left):
        {
            s.insert(s.size(), slot.maxWidth - textLength, ' ');
            break;
        }
        case (SlotAlignment::Right):
        {
            s.insert(0, slot.maxWidth - textLength, ' ');
            break;
        }
        case (SlotAlignment::Center):
        {
            int leftPad = (slot.maxWidth - textLength) / 2;
            s.insert(0, leftPad, ' ');
            s.insert(s.size(), (slot.maxWidth - textLength) - leftPad, ' ');
            break;
        }
        }
    }
    assert((s.length() == static_cast<size_t>(slot.maxWidth)) && "Error in formatting string");
    return s;
}

void NodeRenderer::writeSlot(std::vector<std::string>& grid, Slot slot,
                             std::string_view formattedText) const
{
    assert((formattedText.length() == static_cast<size_t>(slot.maxWidth)) &&
           "Passed a text of wrong format");
    assert((slot.rowIndex >= 0 && slot.rowIndex < m_height) && "Invalid row index");
    assert(slot.columnIndex + slot.maxWidth <= m_width && "Slot too large");

    grid.at(slot.rowIndex).replace(slot.columnIndex, slot.maxWidth, formattedText);
}