#include "connection.h"
#include "commands.h"
#include "game/game.h"
#include "ui/main_window.h"

namespace
{
using namespace ui;
using namespace ui::bridge;

// game -> ui
Commands createUiCommands(MainWindow& mainWindow)
{
    Commands uiCommands;

    uiCommands.setMapCenter = [&mainWindow](const geo::Point& centerPoint) {
        mainWindow.setMapCenter(centerPoint);
    };

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

    return uiCommands;
}

// ui -> game
void connectUiSignals(const MainWindow& mainWindow, game::MapGuesserGame& logicLayer)
{
    QObject::connect(&mainWindow, &MainWindow::startGameRequested,
        [&logicLayer](std::shared_ptr<game::Params> gameParams) {
            logicLayer.onCreateSession(std::move(gameParams));
        });

    QObject::connect(&mainWindow, &MainWindow::nextRoundRequested,
        [&logicLayer]() {
            logicLayer.onStartNextRound();
        });

    QObject::connect(&mainWindow, &MainWindow::guessSubmitted,
        [&logicLayer](const geo::Point& guess) {
            logicLayer.onGuessSubmitted(guess);
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