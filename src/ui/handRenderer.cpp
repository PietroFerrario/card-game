#include "handRenderer.h"
#include "cards/cardInstance.h"
#include "util/debug.h"

std::vector<std::string>
HandRenderer::renderHand(const std::vector<std::unique_ptr<CardInstance>>& handToRender)
{
    if (handToRender.empty())
    {
        DEBUG_LOG("Passed a non-valid list of cards to render");
        return;
    }
    std::vector<std::vector<std::string>> parsedHand(handToRender.size());
    for (const auto& card : handToRender)
    {
        // Check .emplace_back or .assign
        parsedHand.emplace_back(m_cardRenderer.renderCard(*card));
    }

    std::vector<std::string> handToPrint(parsedHand.at(0).size());

    for (auto& renderedCard : parsedHand)
    {
        for (size_t i{0}; i < renderedCard.size(); ++i)
        {
            if (i == 0)
            {
                handToPrint[i] += "    ";
            }
            handToPrint[i] += renderedCard.at(i);
        }
    }
}