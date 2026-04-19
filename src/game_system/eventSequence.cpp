#include "eventSequence.h"
#include "entities/enemies/enemyId.h"
#include "game_events/matchEvent.h"

EventSequence::EventSequence(Player& player) : m_player{player} {}

void EventSequence::resolveEventSequence()
{
    for (auto& event : m_eventList)
    {
        event.resolve();
    }
}