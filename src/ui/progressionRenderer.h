#ifndef PROGRESSIONRENDERER_H
#define PROGRESSIONRENDERER_H

#include "nodeRenderer.h"

#include <string>
#include <vector>

struct EventNode;

class ProgressionRenderer
{
  public:
    ProgressionRenderer() = default;

    std::vector<std::string>
    renderPathOptions(const std::vector<const EventNode*>& optionsToRender) const;

  private:
    NodeRenderer m_nodeRenderer;

    std::string m_gap{"     "};
    const int m_optionLabelWidth{4};
};

#endif // PROGRESSIONRENDERER_H