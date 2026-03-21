#include "engine_fixed_rounds.h"
#include <cassert>

#include "game/params.h"
#include "game/round_results.h"

namespace game::mode
{

FixedRoundsEngine::FixedRoundsEngine(Params&& gameParams)
    : m_gameParams(std::move(gameParams)) { }

const Params& FixedRoundsEngine::params() const
{
    return m_gameParams;
}

RoundResults FixedRoundsEngine::calcRoundResults() const
{
    return RoundResults{m_correctLocation, m_guesses, m_gameParams};
}

double FixedRoundsEngine::getTotalPoints(const TPlayerName& player) const
{
    // TODO
    return 0.0;
}

bool FixedRoundsEngine::isGameOver() const
{
    assert(m_gameParams.roundsCnt > 0);
    return m_roundNumber >= m_gameParams.roundsCnt;
}

void FixedRoundsEngine::registerGuess(const TPlayerName& player, const geo::Point& guess)
{
    assert(!m_guesses.contains(player));
    m_guesses[player] = guess;

    if (m_guesses.size() == m_gameParams.playersCnt())
        notifyRoundFinished();
}

void FixedRoundsEngine::startNextRound(const geo::Point& correctLocation)
{
    ++m_roundNumber;
    m_correctLocation = correctLocation;
    m_guesses.clear();
}

void FixedRoundsEngine::pauseGame()
{
    // TODO
}

}
