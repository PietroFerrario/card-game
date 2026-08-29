#include "progressionRenderer.h"
#include "game_events/eventNode.h"
#include "util/debug.h"

#include <cassert>

std::vector<std::string>
ProgressionRenderer::renderPathOptions(const std::vector<const EventNode*>& optionsToRender) const
{
    if (optionsToRender.empty())
    {
        DEBUG_LOG("No path options to render");
        return {};
    }

    std::vector<std::vector<std::string>> parsedNodeList;
    parsedNodeList.reserve(optionsToRender.size());
    for (const EventNode* node : optionsToRender)
    {
        parsedNodeList.emplace_back(m_nodeRenderer.renderNode(*node));
    }

    // one extra line for the (1) (2) (3) labels
    std::vector<std::string> linesToPrint(parsedNodeList.front().size() + 1);

    for (size_t j{0}; j < parsedNodeList.size(); ++j)
    {
        for (size_t i{0}; i < parsedNodeList[j].size(); ++i)
        {
            if (j > 0)
            {
                linesToPrint[i] += m_gap;
            }
            linesToPrint[i] += parsedNodeList[j][i];
        }
    }

    const size_t count{parsedNodeList.size()};
    const int nodeWidth{m_nodeRenderer.getNodeTemplateWidth()};
    const int gapWidth{static_cast<int>(m_gap.length())};
    const int stride{nodeWidth + gapWidth};

    std::string indexLine;
    indexLine.append(stride * static_cast<int>(count) - gapWidth, ' ');

    for (size_t i{0}; i < count; ++i)
    {
        const size_t displayNum{i + 1};
        std::string label = (displayNum < 10) ? "( " + std::to_string(displayNum) + ")"
                                              : "(" + std::to_string(displayNum) + ")";

        const int nodeStart{stride * static_cast<int>(i)};
        const int labelPos{nodeStart + (nodeWidth - m_optionLabelWidth) / 2};

        assert(label.size() == static_cast<size_t>(m_optionLabelWidth));
        assert(labelPos + m_optionLabelWidth <= static_cast<int>(indexLine.size()));

        indexLine.replace(static_cast<size_t>(labelPos), static_cast<size_t>(m_optionLabelWidth),
                          label);
    }

    linesToPrint.back() = indexLine;

    return linesToPrint;
}