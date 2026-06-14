#ifndef REWARDSRENDERER_H
#define REWARDSRENDERER_H

#include "factories/cardFactory.h"
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
    RewardsRenderer(ICardFactory& cardFactory);

    RenderedRewards renderRewards(const std::vector<RewardOption>& optionsToRender) const;

    std::vector<std::string>
    renderMultipleRewards(const std::vector<std::vector<std::string>>& parsedRewardList,
                          size_t begin, size_t end, size_t indexBase) const;

  private:
    ICardFactory& m_cardFactory;

    RewardOptionRenderer m_rewardOptionRenderer{m_cardFactory};

    std::string m_gap{"          "};
    const int m_optionLabelWidth{4};
};

#endif // REWARDSRENDERER_H
