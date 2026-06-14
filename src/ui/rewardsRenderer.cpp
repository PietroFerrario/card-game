#include "rewardsRenderer.h"
#include "game_events/rewards/rewardOption.h"
#include "util/debug.h"

#include <cassert>

RewardsRenderer::RewardsRenderer(ICardFactory& cardFactory) : m_cardFactory{cardFactory} {}

RenderedRewards
RewardsRenderer::renderRewards(const std::vector<RewardOption>& optionsToRender) const
{
    RenderedRewards renderedRewards;
    if (optionsToRender.empty())
    {
        DEBUG_LOG("You have an empty reward list");
        return renderedRewards;
    }
    std::vector<std::vector<std::string>> parsedRewardList;
    parsedRewardList.reserve(optionsToRender.size());
    for (const auto& option : optionsToRender)
    {
        parsedRewardList.emplace_back(m_rewardOptionRenderer.renderRewardOption(option));
    }

    if (parsedRewardList.size() > 3)
    {
        size_t const halfSize = (parsedRewardList.size() + 1) / 2;

        renderedRewards.firstRow = renderMultipleRewards(parsedRewardList, 0, halfSize, 0);
        renderedRewards.secondRow =
            renderMultipleRewards(parsedRewardList, halfSize, parsedRewardList.size(), halfSize);
    }
    else
    {
        renderedRewards.firstRow =
            renderMultipleRewards(parsedRewardList, 0, parsedRewardList.size(), 0);
    }

    return renderedRewards;
}

std::vector<std::string> RewardsRenderer::renderMultipleRewards(
    const std::vector<std::vector<std::string>>& parsedRewardList, size_t begin, size_t end,
    size_t indexBase) const

{
    assert(begin < end);
    assert(end <= parsedRewardList.size());

    std::vector<std::string> rewardListToPrint(parsedRewardList.at(0).size() + 1);

    for (size_t j{begin}; j < end; ++j)
    {
        bool addGap = {j > begin};

        // rows
        for (size_t i{0}; i < parsedRewardList[j].size(); ++i)
        {
            if (addGap)
            {
                rewardListToPrint[i] += m_gap;
            }
            rewardListToPrint[i] += parsedRewardList[j][i];
        }
    }

    const size_t count = end - begin;

    std::string indexLine;
    const int cardWidth = m_rewardOptionRenderer.getRewardOptionTemplateWidth();
    const int gapWidth = static_cast<int>(m_gap.length());
    const int stride{cardWidth + gapWidth};

    indexLine.append(stride * static_cast<int>(count) - gapWidth, ' ');

    for (size_t i{0}; i < count; ++i)
    {
        const size_t displayNum = indexBase + i + 1;
        std::string label = (displayNum < 10) ? "( " + std::to_string(displayNum) + ")"
                                              : "(" + std::to_string(displayNum) + ")";

        const int cardStart = stride * static_cast<int>(i);
        const int labelPos = cardStart + (cardWidth - m_optionLabelWidth) / 2;

        assert(label.size() == static_cast<size_t>(m_optionLabelWidth));
        assert(labelPos >= 0);
        assert(labelPos + m_optionLabelWidth <= static_cast<int>(indexLine.size()));

        indexLine.replace(static_cast<size_t>(labelPos), static_cast<size_t>(m_optionLabelWidth),
                          label);
    }

    rewardListToPrint.back() = indexLine;

    return rewardListToPrint;
}
