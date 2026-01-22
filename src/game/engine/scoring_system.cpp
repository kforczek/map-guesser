#include "scoring_system.h"
#include "state.h"

namespace game::engine
{

void AdditiveScoringSystem::applyRoundResults(GameState& state, const TPlayer2Points& roundPoints)
{
    assert(roundPoints.size() == state.gamePoints.size());

    for (TPlayerId playerId = 0; playerId < roundPoints.size(); ++playerId)
        state.gamePoints[playerId] += roundPoints[playerId];
}

}
