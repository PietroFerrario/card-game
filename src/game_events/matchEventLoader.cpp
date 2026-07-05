#include "matchEventLoader.h"
#include "gameEvent.h"

#include <cassert>
#include <fstream>

using json = nlohmann::json;

MatchEventLoader::MatchEventLoader()
{
    std::ifstream f("data/eventList.json");
    assert(f.is_open() && "Failed to open matches json");
    m_data = json::parse(f);
}

std::vector<EventData> MatchEventLoader::loadEvents()
{

    const json& eventList = m_data.at("eventList");

    std::vector<EventData> eventDataList;

    for (const auto& entry : eventList)
    {
        const std::string& type{entry.at("type").get_ref<const std::string&>()};

        if (type == "match")
        {
            MatchEventData match;
            match.enemyId = m_enemyIdMap.at(entry.at("enemyId").get_ref<const std::string&>());
            match.rewardListId = entry.at("rewardListId").get_ref<const std::string&>();

            eventDataList.emplace_back(std::move(match));
        }
        else if (type == "story")
        {
            StoryEventData story;
            story.storyId = entry.at("storyId").get_ref<const std::string&>();
            story.title = entry.at("storyTitle").get_ref<const std::string&>();
            story.storyDescription = entry.at("storyDescription").get_ref<const std::string&>();
            story.rewardListId = entry.at("rewardListId").get_ref<const std::string&>();

            eventDataList.emplace_back(std::move(story));
        }
    }

    return eventDataList;
}
