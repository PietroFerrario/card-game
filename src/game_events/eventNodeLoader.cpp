#include "eventNodeLoader.h"
#include "gameEvent.h"

#include <cassert>
#include <fstream>

using json = nlohmann::json;

EventNodeLoader::EventNodeLoader()
{
    std::ifstream f("data/eventList.json");
    assert(f.is_open() && "Failed to open matches json");
    m_data = json::parse(f);
}

std::vector<EventNodeData> EventNodeLoader::loadEventNodes()
{

    const json& eventList = m_data.at("eventList");

    std::vector<EventNodeData> eventNodeDataList;

    for (const auto& entry : eventList)
    {
        std::string id{entry.at("id").get_ref<const std::string&>()};
        std::vector<std::string> next;
        for (const auto& nextId : entry.at("next"))
        {
            next.emplace_back(nextId.get_ref<const std::string&>());
        }
        std::string prevDescription{entry.at("prevDescription").get_ref<const std::string&>()};
        int layer{entry.at("layer").get<int>()};
        int column{entry.at("column").get<int>()};

        const std::string& type{entry.at("type").get_ref<const std::string&>()};

        if (type == "match")
        {
            eventNodeDataList.emplace_back(id, next, prevDescription, loadMatchEvent(entry), layer,
                                           column);
        }
        else if (type == "story")
        {
            eventNodeDataList.emplace_back(id, next, prevDescription, loadStoryEvent(entry), layer,
                                           column);
        }
    }

    return eventNodeDataList;
}

MatchEventData EventNodeLoader::loadMatchEvent(const json& matchData)
{
    return {matchData.at("enemyId").get_ref<const std::string&>(),
            matchData.at("rewardListId").get_ref<const std::string&>()};
}

StoryEventData EventNodeLoader::loadStoryEvent(const json& storyData)
{
    return {storyData.at("storyId").get_ref<const std::string&>(),
            storyData.at("storyTitle").get_ref<const std::string&>(),
            storyData.at("storyDescription").get_ref<const std::string&>(),
            storyData.at("rewardListId").get_ref<const std::string&>()};
}