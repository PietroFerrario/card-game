#ifndef HANDRENDER_H
#define HANDRENDER_H

#include "cardRenderer.h"

#include <memory>
#include <vector>

class CardInstance;

class HandRenderer
{
  public:
    std::vector<std::string>
    renderHand(const std::vector<std::unique_ptr<CardInstance>>& handToRender);

  private:
    CardRenderer m_cardRenderer{};
};

#endif // HANDRENDER_H