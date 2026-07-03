#include "engine_server_fixed_rounds.h"
#include <cassert>

#include "params.h"
#include "round_results.h"

namespace game
{

FixedRoundsServerEngine::FixedRoundsServerEngine(Params&& gameParams, IEngineStateObserver& observer)
    : EngineBase(observer)
    , m_gameParams(std::move(gameParams)) { }

const Params& FixedRoundsServerEngine::params() const
{
    return m_gameParams;
}

RoundResults FixedRoundsServerEngine::calcRoundResults() const
{
    return RoundResults{m_correctLocation, m_guesses, m_gameParams};
}

double FixedRoundsServerEngine::getTotalPoints(const TPlayerName& player) const
{
    // TODO
    return 0.0;
}

bool FixedRoundsServerEngine::isGameOver() const
{
    assert(m_gameParams.roundsCnt > 0);
    return m_roundNumber >= m_gameParams.roundsCnt;
}

void FixedRoundsServerEngine::registerPlayerGuess(const TPlayerName& player, const std::optional<geo::Point>& guess)
{
    assert(!m_guesses.contains(player));
    m_guesses[player] = guess;

    if (m_guesses.size() == m_gameParams.playersCnt())
        notifyRoundFinished();
}

void FixedRoundsServerEngine::startNextRound(const geo::Point& correctLocation)
{
    ++m_roundNumber;
    m_correctLocation = correctLocation;
    m_guesses.clear();
}

void FixedRoundsServerEngine::pauseGame()
{
    // TODO
}

}
