#include "rewardOptionRenderer.h"

#include <cassert>

std::vector<std::string>
RewardOptionRenderer::renderRewardOption(const RewardOption& optionToRender) const
{
    std::vector<std::string> grid(m_height, std::string(m_width, ' '));

    drawTemplate(grid);

    NameLayout nameLayout{drawLayout(optionToRender.getName(), m_firstNameSlot)};

    writeSlot(grid, m_firstNameSlot, fitText(m_firstNameSlot, nameLayout.firstName));

    if (nameLayout.secondName.has_value())
    {
        writeSlot(grid, m_secondNameSlot, fitText(m_secondNameSlot, *nameLayout.secondName));
    }

    std::vector<std::string> descriptionLayout{
        drawDescriptionLayout(optionToRender.getDescription(), m_descriptionSlots.front())};

    for (int i{0}; i < descriptionLayout.size(); i++)
    {
        writeSlot(grid, m_descriptionSlots.at(i),
                  fitText(m_descriptionSlots.at(i), descriptionLayout.at(i)));
    }
    return grid;
}

void RewardOptionRenderer::drawTemplate(std::vector<std::string>& grid) const
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
}

void RewardOptionRenderer::appendWord(std::string& line, std::string_view word)
{
    if (word.empty())
        return;
    if (!line.empty())
        line.push_back(' ');
    line.append(word);
}

void RewardOptionRenderer::appendSeparator(std::string& line, std::string_view word)
{
    if (word.empty())
        return;
    if (!line.empty())
        line.append(" | ");
    line.append(word);
}

NameLayout RewardOptionRenderer::drawLayout(std::string_view rewardOptionName,
                                            Slot currentSlot) const
{
    NameLayout newName;

    if (rewardOptionName.length() <= static_cast<size_t>(currentSlot.maxWidth))
    {
        newName.firstName = std::string(rewardOptionName);
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

    for (const auto c : rewardOptionName)
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

std::vector<std::string>
RewardOptionRenderer::drawDescriptionLayout(std::string_view rewardOptionDescription,
                                            Slot currentSlot) const
{
    std::vector<std::string> lines;

    if (rewardOptionDescription.length() <= static_cast<size_t>(currentSlot.maxWidth))
    {
        lines.emplace_back(rewardOptionDescription);
        return lines;
    }

    std::string currentWord;

    lines.resize(m_descriptionMaxLines);
    int currentLineIndex{0};

    auto commitWord = [&](std::string_view word) -> void
    {
        if (word.empty())
            return;
        else
        {
            size_t charNeeded{0};
            if (lines.at(currentLineIndex).empty())
                charNeeded = word.length();
            else
            {
                charNeeded = word.length() + lines.at(currentLineIndex).length() + 1;
            }

            if (charNeeded <= static_cast<size_t>(currentSlot.maxWidth))
            {
                appendWord(lines.at(currentLineIndex), word);
            }
            else
            {
                if (currentLineIndex < m_descriptionMaxLines - 1)
                {
                    ++currentLineIndex;
                    appendWord(lines.at(currentLineIndex), word);
                }
            }
        }
    };

    for (const auto c : rewardOptionDescription)
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

    while (!lines.empty() && lines.back() == "")
    {
        lines.pop_back();
    }

    return lines;
}

std::string RewardOptionRenderer::fitText(Slot slot, std::string_view text) const
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

void RewardOptionRenderer::writeSlot(std::vector<std::string>& grid, Slot slot,
                                     std::string_view formattedText) const
{
    assert((formattedText.length() == slot.maxWidth) && "Passed a text of wrong format");
    assert((slot.rowIndex >= 0 && slot.rowIndex < m_height) && "Invalid row index");
    assert((slot.columnIndex >= 0 && slot.columnIndex < m_width) && "Invalid column index");
    assert(slot.columnIndex + slot.maxWidth <= m_width && "Slot too large");

    grid.at(slot.rowIndex).replace(slot.columnIndex, slot.maxWidth, formattedText);
}