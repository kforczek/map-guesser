#include "game.h"
#include "random_point.h"
#include <cassert>

namespace game
{

void MapGuesserGame::setUiCommands(ui::bridge::Commands commands)
{
    m_uiCommands = std::move(commands);
}

void MapGuesserGame::onCreateSession(Params&& gameParams)
{
    m_gameSession = Session{std::move(gameParams), *this};

    onNextRoundRequested();
}

// ReSharper disable CppMemberFunctionMayBeConst
void MapGuesserGame::onNextRoundRequested()
{
    assert(m_gameSession);
    if (m_gameSession->engine().isGameOver())
    {
        showGameSummary();
    }
    else
    {
        startNextRound();
    }
}
// ReSharper restore CppMemberFunctionMayBeConst

void MapGuesserGame::onPlayerFinishedRound(const std::optional<geo::Point>& guessedLocation)
{
    assert(m_gameSession);
    m_gameSession->engine().registerPlayerGuess("", guessedLocation);

    onRoundFinished();
}

void MapGuesserGame::onRoundFinished()
{
    assert(m_gameSession);

    RoundResults roundResults = m_gameSession->engine().calcRoundResults();
    m_roundsHistory.push_back(std::move(roundResults));

    m_uiCommands.showRoundResults(m_roundsHistory.back(), m_gameSession->engine().isGameOver());
}

void MapGuesserGame::startNextRound()
{
    assert(m_gameSession);

    std::optional<geo::Point> location;
    while (!location)
    {
        try
        {
            location = game::GetRandomStreetViewPoint(m_gameSession->params().projectedMap);
        }
        catch (std::runtime_error& err)
        {
            const auto decision = m_uiCommands.showErrorMessage(err.what());
            if (decision == ui::bridge::Commands::ErrorAction::Abort)
                exit(1);
        }
    }

    m_uiCommands.startNextRound(*location);
    m_gameSession->engine().startNextRound(*location);
}

void MapGuesserGame::showGameSummary()
{
    // TODO: multiplayer
    // TODO: game modes with different initial points
    m_uiCommands.showGameSummary({""}, m_roundsHistory, 0);
}

}
