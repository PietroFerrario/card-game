#ifndef EVENTSEQUENCE_H
#define EVENTSEQUENCE_H

#include "entities/player.h"
#include "game_events/gameEvent.h"
#include "ui/terminalMatchView.h"
#include <vector>

class EventSequence
{
  public:
    EventSequence(Player& player);
    void resolveEventSequence();

  private:
    Player& m_player;
    TerminalMatchView m_terminalMatchView;
    std::vector<GameEvent> m_eventList;
};

#endif // EVENTSEQUENCE_H