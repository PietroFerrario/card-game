#ifndef HANDRENDER_H
#define HANDRENDER_H

#include "cardRenderer.h"

#include <memory>
#include <vector>

class CardInstance;

struct RenderedHand
{
    std::optional<std::vector<std::string>> firstRow;
    std::optional<std::vector<std::string>> secondRow;
};

class HandRenderer
{
  public:
    RenderedHand renderHand(const std::vector<const CardInstance*>& handToRender);
    std::vector<std::string>
    renderMultipleCards(const std::vector<std::vector<std::string>>& parsedHand, size_t begin,
                        size_t end, size_t indexBase);

  private:
    CardRenderer m_cardRenderer{};

    std::string m_gap{"    "};
    const int m_cardLabelWidth{4};
};

#endif // HANDRENDER_H