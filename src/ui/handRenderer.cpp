#include "handRenderer.h"
#include "cards/cardInstance.h"
#include "util/debug.h"

#include <cassert>

RenderedHand HandRenderer::renderHand(const std::vector<const CardInstance*>& handToRender)
{
    RenderedHand renderedHand;
    if (handToRender.empty())
    {
        DEBUG_LOG("You have an empty hand");
        return renderedHand;
    }
    std::vector<std::vector<std::string>> parsedHand;
    parsedHand.reserve(handToRender.size());
    for (const auto& card : handToRender)
    {
        parsedHand.emplace_back(m_cardRenderer.renderCard(*card));
    }

    if (parsedHand.size() > 7)
    {
        size_t const halfSize = (parsedHand.size() + 1) / 2;

        renderedHand.firstRow = renderMultipleCards(parsedHand, 0, halfSize, 0);
        renderedHand.secondRow =
            renderMultipleCards(parsedHand, halfSize, parsedHand.size(), halfSize);
    }
    else
    {
        renderedHand.firstRow = renderMultipleCards(parsedHand, 0, parsedHand.size(), 0);
    }

    return renderedHand;
}

std::vector<std::string>
HandRenderer::renderMultipleCards(const std::vector<std::vector<std::string>>& parsedHand,
                                  size_t begin, size_t end, size_t indexBase)
{
    assert(begin < end);
    assert(end <= parsedHand.size());

    std::vector<std::string> handToPrint(parsedHand.at(0).size() + 1);

    for (size_t j{begin}; j < end; ++j)
    {
        bool addGap = {j > begin};

        // rows
        for (size_t i{0}; i < parsedHand[j].size(); ++i)
        {
            if (addGap)
            {
                handToPrint[i] += m_gap;
            }
            handToPrint[i] += parsedHand[j][i];
        }
    }

    const size_t count = end - begin;

    std::string indexLine;
    const int cardWidth = m_cardRenderer.getCardTemplateWidth();
    const int gapWidth = static_cast<int>(m_gap.length());
    const int stride{cardWidth + gapWidth};

    indexLine.append(stride * static_cast<int>(count) - gapWidth, ' ');

    for (size_t i{0}; i < count; ++i)
    {
        const size_t displayNum = indexBase + i + 1;
        std::string label = (displayNum < 10) ? "( " + std::to_string(displayNum) + ")"
                                              : "(" + std::to_string(displayNum) + ")";

        const int cardStart = stride * static_cast<int>(i);
        const int labelPos = cardStart + (cardWidth - m_cardLabelWidth) / 2;

        assert(label.size() == static_cast<size_t>(m_cardLabelWidth));
        assert(labelPos >= 0);
        assert(labelPos + m_cardLabelWidth <= static_cast<int>(indexLine.size()));

        indexLine.replace(static_cast<size_t>(labelPos), static_cast<size_t>(m_cardLabelWidth),
                          label);
    }

    handToPrint.back() = indexLine;

    return handToPrint;
}
