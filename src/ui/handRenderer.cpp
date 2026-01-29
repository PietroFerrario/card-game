#include "handRenderer.h"
#include "cards/cardInstance.h"
#include "util/debug.h"

#include <cassert>

std::vector<std::string>
HandRenderer::renderHand(const std::vector<const CardInstance*>& handToRender)
{
    // Need to fix the empty return?
    if (handToRender.empty())
    {
        DEBUG_LOG("Passed an empty hand");
        return std::vector<std::string>{};
    }
    std::vector<std::vector<std::string>> parsedHand;
    parsedHand.reserve(handToRender.size());
    for (const auto& card : handToRender)
    {
        // Check .emplace_back or .assign
        parsedHand.emplace_back(m_cardRenderer.renderCard(*card));
    }

    std::vector<std::string> handToPrint(parsedHand.at(0).size() + 1);

    for (size_t j{0}; j < parsedHand.size(); ++j)
    {
        bool addGap = {j > 0};

        for (size_t i{0}; i < parsedHand[j].size(); ++i)
        {
            if (addGap)
            {
                handToPrint[i] += m_gap;
            }
            handToPrint[i] += parsedHand[j][i];
        }
    }

    std::string indexLine;
    int cardWidth = m_cardRenderer.getCardTemplateWidth();
    int gapWidth = static_cast<int>(m_gap.length());
    int stride{cardWidth + gapWidth};
    indexLine.append(((stride) * static_cast<int>(parsedHand.size())) - gapWidth, ' ');

    for (size_t i{0}; i < parsedHand.size(); ++i)
    {
        std::string label;
        if (i < 9)
        {
            label = {"( " + std::to_string(i + 1) + ")"};
        }
        else
        {
            label = {"(" + std::to_string(i + 1) + ")"};
        }
        int cardStart = stride * i;
        int labelPos = cardStart + (cardWidth - m_cardLabelWidth) / 2;

        assert(label.size() == m_cardLabelWidth);
        assert(labelPos >= 0);
        assert(labelPos + m_cardLabelWidth <= indexLine.size());
        indexLine.replace(labelPos, m_cardLabelWidth, label);
    }

    handToPrint.back() = indexLine;

    return handToPrint;
}