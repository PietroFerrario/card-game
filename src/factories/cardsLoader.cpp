#include "cards/cardDefinition.h"
#include "cards/cardParams.h"

#include "cardsLoader.h"
#include <cassert>
#include <fstream>

using json = nlohmann::json;

CardsLoader::CardsLoader()
{
    std::ifstream f("data/cards.json");
    assert(f.is_open() && "Failed to open cards json");
    m_data = json::parse(f);
}

std::vector<std::unique_ptr<CardDefinition>> CardsLoader::parseCardsList()
{
    std::vector<std::unique_ptr<CardDefinition>> cardsDefinitionList;

    for (const auto& card : m_data.at("cardList"))
    {
        cardsDefinitionList.emplace_back(std::move(loadCard(card)));
    }

    return cardsDefinitionList;
}

std::unique_ptr<CardDefinition> CardsLoader::loadCard(const json& card)
{
    return std::make_unique<CardDefinition>(
        card.at("id").get_ref<const std::string&>(), card.at("name").get_ref<const std::string&>(),
        card.at("descr").get_ref<const std::string&>(),
        CardParams{.damage = card.at("damage").get<int>(),
                   .armor = card.at("armor").get<int>(),
                   .actions = card.at("actions").get<int>(),
                   .drawing = card.at("drawing").get<int>()},
        m_effectFactory.makeEffectList(makeEffectDataList(card.at("effectList"))),
        card.contains("cardDisposalMode")
            ? card::cardDisposalModeMap.at(
                  card.at("cardDisposalMode").get_ref<const std::string&>())
            : CardDisposalMode::Discard);
}

std::vector<std::pair<EffectName, Target>>
CardsLoader::makeEffectDataList(const json& jsonEffectList)
{
    std::vector<std::pair<EffectName, Target>> effectList;

    for (const auto& jsonEffect : jsonEffectList)
    {

        EffectName effectName{
            effect::effectNameMap.at(jsonEffect.at("effect").get_ref<const std::string&>())};

        const auto& targetJson{jsonEffect.at("target")};
        Target target{targetJson.is_null()
                          ? Target::Self
                          : target::targetMap.at(targetJson.get_ref<const std::string&>())};

        effectList.emplace_back(std::pair<EffectName, Target>{effectName, target});
    }
    return effectList;
}
