#include "engine_fixed_rounds.h"

#include "game/params.h"
#include "game/round_results.h"

namespace game::mode
{

FixedRoundsEngine::FixedRoundsEngine(std::shared_ptr<Params> gameParams)
    : m_gameParams(std::move(gameParams)) { }

double FixedRoundsEngine::getTotalPoints(const TPlayerName& player) const
{
    // TODO
    return 0.0;
}

bool FixedRoundsEngine::isGameOver() const
{
    // TODO
    return false;
}

void FixedRoundsEngine::registerGuess(const TPlayerName& player, const geo::Point& guess)
{
    m_guesses[player] = guess;

    const bool allPlayersGuessed = m_guesses.size() == m_gameParams->playersCnt();
    if (allPlayersGuessed)
        finishRound();
}

void FixedRoundsEngine::startNextRound(const geo::Point& correctLocation)
{
    m_correctLocation = correctLocation;
}

void FixedRoundsEngine::pauseGame()
{
    // TODO
}

void FixedRoundsEngine::finishRound()
{
    const RoundResults roundResults{m_correctLocation, m_guesses, *m_gameParams};
    notifyRoundFinished(roundResults);
}

}
