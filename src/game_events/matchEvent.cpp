#include "matchEvent.h"
#include "cards/cardDefinition.h"
#include "game_system/cardmatch.h"
#include "util/debug.h"

MatchEvent::MatchEvent(IMatchView& matchView, Player& player, EnemyId enemyId,
                       const std::vector<DeckEntry> rewardCardList)
    : m_matchView{matchView}, m_enemyId{enemyId}, m_player{player}, m_rewardCardList{rewardCardList}
{
}

void MatchEvent::resolve()
{
    auto enemy{EnemyFactory::makeEnemy(m_enemyId)};
    if (enemy)
    {
        m_enemyName = enemy->getName();
        CardMatch cardMatch{m_matchView, m_player, *enemy};
        MatchData matchResult{cardMatch.turnLoop()};

        if (matchResult.matchState == MatchState::PlayerWon)
        {
            rewardPhase();
        }
        else if (matchResult.matchState == MatchState::EnemyWon)
        {
            DEBUG_LOG("GameOver from MatchEvent");
        }
    }
    else
    {
        DEBUG_LOG("Invalid enemy selection for the MatchEvent!");
    }
}

// Evaluate to take the CardFactory out of the CardMatch and pass it to it rather, so could be
// shared with reward phase
// void MatchEvent::rewardPhase()
// {
//     CardFactory cardFactory;

//     std::vector<std::unique_ptr<CardInstance>> rewardCardSelection;

//     for (const auto& deckEntry : m_rewardCardList)
//     {
//         for (int i{0}; i < deckEntry.cardCount; ++i)
//         {
//             rewardCardSelection.emplace_back(cardFactory.makeSingleCard(deckEntry.cardId));
//         }
//     }
//     std::vector<const CardInstance*> cardsView;
//     cardsView.reserve(rewardCardSelection.size());

//     for (const std::unique_ptr<CardInstance>& currentCard : rewardCardSelection)
//     {
//         cardsView.emplace_back(currentCard.get());
//     }

//     m_matchView.showRewardText(m_enemyName);
//     m_matchView.showCurrentHand(cardsView);

//     RewardDecision decision{
//         m_matchView.askPlayerReward(static_cast<int>(rewardCardSelection.size()))};

//     if (decision.playerChoice == RewardChoice::SelectReward)
//     {
//         DEBUG_LOG("Selected reward" << decision.selectedCard.value());

//         m_player.getDeckPlayer().addCard(
//             rewardCardSelection.at(decision.selectedCard.value())->getCardDefinition().getID());
//         m_matchView.showReward(
//             rewardCardSelection.at(decision.selectedCard.value())->getCardDefinition().getName());
//     }
//     else if (decision.playerChoice == RewardChoice::SkipReward)
//     {
//         DEBUG_LOG("Skipping reward");
//     }
// }
