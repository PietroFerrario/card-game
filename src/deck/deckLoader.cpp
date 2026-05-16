#include "deckLoader.h"

#include <cassert>
#include <fstream>

using json = nlohmann::json;

DeckLoader::DeckLoader()
{
    std::ifstream f("data/decks.json");
    assert(f.is_open() && "Failed to open decks json");
    m_data = json::parse(f);
}

std::vector<DeckEntry> DeckLoader::loadDeck(std::string_view deckName)
{
    const json& deck = m_data.at(deckName);

    std::vector<DeckEntry> initialCardsList;

    for (const auto& entry : deck)
    {
        if (entry.at("amount").get<int>() > 0)
        {
            initialCardsList.emplace_back(DeckEntry{entry.at("id").get_ref<const std::string&>(),
                                                    entry.at("amount").get<int>()});
        }
    }

    return initialCardsList;
}
