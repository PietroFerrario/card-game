#include "cardRenderer.h"
#include "cards/cardDefinition.h"
#include "cards/cardInstance.h"

#include <cassert>
#include <iostream>

std::vector<std::string> CardRenderer::renderCard(const CardInstance& cardToRender)
{
    std::vector<std::string> grid(m_height, std::string(m_width, ' '));

    drawTemplate(grid);

    NameLayout nameLayout{drawLayout(cardToRender.getCardDefinition().getName(), m_firstNameSlot)};

    writeSlot(grid, m_firstNameSlot, fitText(m_firstNameSlot, nameLayout.firstName));

    if (nameLayout.secondName.has_value())
    {
        writeSlot(grid, m_secondNameSlot, fitText(m_secondNameSlot, *nameLayout.secondName));
    }

    writeSlot(grid, m_damageValueSlot,
              fitText(m_damageValueSlot, std::to_string(cardToRender.getDamage())));
    writeSlot(grid, m_armorValueSlot,
              fitText(m_armorValueSlot, std::to_string(cardToRender.getArmor())));

    NameLayout descriptionLayout{
        drawLayout(cardToRender.getCardDefinition().getDescription(), m_firstDescrSlot)};

    writeSlot(grid, m_firstDescrSlot, fitText(m_firstDescrSlot, descriptionLayout.firstName));

    if (descriptionLayout.secondName.has_value())
    {
        writeSlot(grid, m_secondDescrSlot,
                  fitText(m_secondDescrSlot, *descriptionLayout.secondName));
    }

    return grid;
}

void CardRenderer::drawTemplate(std::vector<std::string>& grid)
{

    // Top/bottom border
    grid.at(0).assign(m_width, m_horizontalBorder);
    grid.at(m_height - 1).assign(m_width, m_horizontalBorder);

    // Right/left border
    for (int i{1}; i < m_height - 1; ++i)
    {
        grid.at(i).replace(0, 1, 1, m_verticalBorder);
        grid.at(i).replace(m_width - 1, 1, 1, m_verticalBorder);
    }

    writeSlot(grid, m_atkLabelSlot, "[ATK] ");
    writeSlot(grid, m_defLabelSlot, "[DEF] ");
}

void CardRenderer::appendWord(std::string& line, std::string_view word)
{
    if (word.empty())
        return;
    if (!line.empty())
        line.push_back(' ');
    line.append(word);
}

NameLayout CardRenderer::drawLayout(std::string_view cardName, Slot currentSlot)
{
    NameLayout newName;

    if (cardName.length() <= static_cast<size_t>(currentSlot.maxWidth))
    {
        newName.firstName = std::string(cardName);
        return newName;
    }

    std::string currentWord;
    std::string lineOne;
    std::string lineTwo;

    bool overFlowed{false};

    auto commitWord = [&](std::string_view word) -> void
    {
        if (word.empty())
            return;

        if (overFlowed)
        {
            appendWord(lineTwo, word);
        }
        else
        {
            size_t charNeeded{0};
            if (lineOne.empty())
                charNeeded = word.length();
            else
            {
                charNeeded = word.length() + lineOne.length() + 1;
            }

            if (charNeeded <= static_cast<size_t>(currentSlot.maxWidth))
            {
                appendWord(lineOne, word);
            }
            else
            {
                overFlowed = true;
                appendWord(lineTwo, word);
            }
        }
    };

    for (const auto c : cardName)
    {
        if (c != ' ')
        {
            currentWord += c;
        }
        else
        {
            commitWord(currentWord);
            currentWord.clear();
        }
    }
    commitWord(currentWord);

    newName.firstName = lineOne;
    if (overFlowed)
    {
        newName.secondName.emplace(lineTwo);
    }

    return newName;
}

std::string CardRenderer::fitText(Slot slot, std::string_view text)
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
    assert((s.length() == slot.maxWidth) && "Error in formatting string");
    return s;
}

void CardRenderer::writeSlot(std::vector<std::string>& grid, Slot slot,
                             std::string_view formattedText)
{
    assert((formattedText.length() == slot.maxWidth) && "Passed a text of wrong format");
    assert((slot.rowIndex >= 0 && slot.rowIndex < m_height) && "Invalid row index");
    assert((slot.columnIndex >= 0 && slot.columnIndex < m_width) && "Invalid column index");
    assert(slot.columnIndex + slot.maxWidth <= m_width && "Slot too large");

    grid.at(slot.rowIndex).replace(slot.columnIndex, slot.maxWidth, formattedText);
}