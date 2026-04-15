#include "matchEvent.h"
#include "game_system/cardmatch.h"
#include "util/debug.h"

MatchEvent::MatchEvent(IMatchView& matchView, Player& player, EnemyId enemyId)
    : m_matchView{matchView}, m_enemyId{enemyId}, m_player{player}
{
}

void MatchEvent::resolve()
{
    auto enemy{EnemyFactory::makeEnemy(m_enemyId)};
    if (enemy)
    {
        CardMatch cardMatch{m_matchView, m_player, *enemy};
        cardMatch.turnLoop();
    }
    else
    {
        DEBUG_LOG("Invalid enemy selection for the MatchEvent!");
    }
}