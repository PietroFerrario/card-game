#ifndef EVENTNODE_H
#define EVENTNODE_H

#include "game_events/gameEvent.h"

#include <memory>
#include <string>
#include <vector>

struct EventNode
{
    EventNode(std::string id, std::unique_ptr<GameEvent> event, std::vector<int> next,
              std::string_view previewDescription, int layer, int column)
        : id{id}, event{std::move(event)}, nextNodeList{std::move(next)},
          previewDescription{previewDescription}, layer{layer}, column{column}
    {
    }

    std::string id;

    std::unique_ptr<GameEvent> event;
    std::vector<int> nextNodeList;

    int layer{};  // progression
    int column{}; // left-right-center

    std::string previewDescription;
};

#endif // EVENTNODE_H