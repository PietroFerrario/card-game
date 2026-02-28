#ifndef DECKLOADER_H
#define DECKLOADER_H

#include "deckEntry.h"

#include <nlohmann/json.hpp>
#include <string_view>
#include <vector>

class DeckLoader
{
  public:
    DeckLoader();

    std::vector<DeckEntry> loadDeck(std::string_view deckName);

  private:
    nlohmann::json m_data{};
};

#endif // DECKLOADER_H