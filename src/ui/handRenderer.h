#ifndef HANDRENDER_H
#define HANDRENDER_H

#include "cardRenderer.h"

#include <memory>
#include <vector>

class CardInstance;

class HandRenderer
{
  public:
    std::vector<std::string> renderHand(const std::vector<const CardInstance*>& handToRender);

  private:
    CardRenderer m_cardRenderer{};

    std::string m_gap{"    "};
    const int m_cardLabelWidth{4};
};

#endif // HANDRENDER_H