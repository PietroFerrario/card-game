#ifndef REWARDSRENDERER_H
#define REWARDSRENDERER_H

#include "rewardOptionRenderer.h"

#include <memory>
#include <optional>
#include <vector>

class RewardOption;

struct RenderedRewards
{
    std::optional<std::vector<std::string>> firstRow;
    std::optional<std::vector<std::string>> secondRow;
};

class RewardsRenderer
{
  public:
    RenderedRewards renderRewards(const std::vector<RewardOption>& optionsToRender) const;

    std::vector<std::string>
    renderMultipleRewards(const std::vector<std::vector<std::string>>& parsedRewardList,
                          size_t begin, size_t end, size_t indexBase) const;

  private:
    RewardOptionRenderer m_rewardOptionRenderer{};

    std::string m_gap{"       "};
    const int m_optionLabelWidth{4};
};

#endif // REWARDSRENDERER_H