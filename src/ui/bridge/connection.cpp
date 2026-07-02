#include "connection.h"
#include "commands.h"
#include "game/game.h"
#include "game/params.h"
#include "lambert/projection.h"
#include "ui/main_window.h"
#include "ui/params.h"

namespace
{
using namespace ui;
using namespace ui::bridge;

// ##################################################################################################################

game::Params toLogicLayerParams(const ui::Params& uiParams)
{
    game::Params gameParams;

    gameParams.projectedMap = lambert::project(uiParams.map);
    gameParams.roundsCnt = uiParams.roundsCnt;
    gameParams.maxRoundPoints = uiParams.maxRoundPoints;

    // TODO: player names - to be removed from backend?
    gameParams.playerNames.reserve(uiParams.playerNames.size());
    for (const auto& playerName : uiParams.playerNames)
        gameParams.playerNames.push_back(playerName.toStdString());

    return gameParams;
}

// ##################################################################################################################

// game -> ui
Commands createUiCommands(MainWindow& mainWindow)
{
    Commands uiCommands;

    uiCommands.startNextRound = [&mainWindow](const geo::Point& location) {
        mainWindow.startNextRound(location);
    };

    uiCommands.showPlayerGuessed = [&mainWindow](const std::string& playerName) {
        mainWindow.showPlayerGuessed(playerName);
    };

    uiCommands.showRoundResults = [&mainWindow](const game::RoundResults& roundResults, bool isGameOver) {
        mainWindow.showRoundResults(roundResults, isGameOver);
    };

    uiCommands.showErrorMessage = [&mainWindow](const std::string& what) {
        const QMessageBox::StandardButton bt = mainWindow.showErrorMessage(QString::fromStdString(what));
        return bt == QMessageBox::Retry ? Commands::ErrorAction::Retry : Commands::ErrorAction::Abort;
    };

    uiCommands.showGameSummary = [&mainWindow](
        const std::vector<std::string>& leaderboard,
        const std::vector<game::RoundResults>& roundsHistory,
        int initialPoints
    ) {
        mainWindow.showGameSummary(leaderboard, roundsHistory, initialPoints);
    };

    return uiCommands;
}

// ui -> game
void connectUiSignals(const MainWindow& mainWindow, game::MapGuesserGame& logicLayer)
{
    QObject::connect(&mainWindow, &MainWindow::startGameRequested,
        [&logicLayer](const ui::Params& uiParams) {
            logicLayer.onCreateSession(toLogicLayerParams(uiParams));
        });

    QObject::connect(&mainWindow, &MainWindow::nextRoundRequested,
        [&logicLayer]() {
            logicLayer.onNextRoundRequested();
        });

    QObject::connect(&mainWindow, &MainWindow::playerFinishedRound,
        [&logicLayer](const std::optional<geo::Point>& guess) {
            logicLayer.onPlayerFinishedRound(guess);
        });
}

}

namespace ui::bridge
{

void Connect(game::MapGuesserGame& logicLayer, MainWindow& mainWindow)
{
    Commands uiCommands = createUiCommands(mainWindow);
    logicLayer.setUiCommands(std::move(uiCommands));

    connectUiSignals(mainWindow, logicLayer);
}

}