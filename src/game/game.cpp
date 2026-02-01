#include "game.h"

#include "random_point.h"
#include "ui/main_window.h"

namespace game
{

void MapGuesserGame::setUiCommands(ui::bridge::Commands commands)
{
    m_uiCommands = std::move(commands);
}

void MapGuesserGame::onCreateSession(std::shared_ptr<Params> gameParams)
{
    m_gameSession = Session{std::move(gameParams), *this};

    const geo::Point& centerPoint = m_gameSession->params().geoMap.center();
    m_uiCommands.setMapCenter(centerPoint);

    onStartNextRound();
}

// ReSharper disable CppMemberFunctionMayBeConst
void MapGuesserGame::onStartNextRound()
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
// ReSharper restore CppMemberFunctionMayBeConst

void MapGuesserGame::onGuessSubmitted(const geo::Point& guessedLocation)
{
    assert(m_gameSession);
    m_gameSession->engine().registerGuess("", guessedLocation);
}

void MapGuesserGame::onRoundFinished(const RoundResults &roundResults) const
{
    assert(m_gameSession);
    m_uiCommands.showRoundResults(roundResults, m_gameSession->engine().isGameOver());
}

}
