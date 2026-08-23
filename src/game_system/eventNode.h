#ifndef EVENTNODE_H
#define EVENTNODE_H

#include "game_events/gameEvent.h"

#include <memory>
#include <string>

struct EventNode
{
    EventNode(std::unique_ptr<GameEvent> event, std::vector<int> nextNodeList, int layer,
              int column, std::string_view descr)
        : m_event{std::move(event)}, m_nextNodeList{std::move(nextNodeList)}, m_layer{layer},
          m_column{column}, m_previewDescription{descr}
    {
    }

    std::unique_ptr<GameEvent> m_event;
    std::vector<int> m_nextNodeList;

    int m_layer{};  // progression
    int m_column{}; // left-right-center

    std::string m_previewDescription;
};

#endif // EVENTNODE_H