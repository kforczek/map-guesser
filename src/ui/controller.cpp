#include "controller.h"
#include "main_window.h"
#include "game/game.h"

namespace ui
{

// TODO: free ui::Connect() function if controller stays ctor-only
Controller::Controller(game::MapGuesserGame& logicLayer, MainWindow& mainWindow)
{
    // ui -> game
    connect(&mainWindow, &MainWindow::startGameRequested,
        [&logicLayer](std::shared_ptr<game::Params> gameParams) {
            logicLayer.onCreateSession(std::move(gameParams));
        });

    connect(&mainWindow, &MainWindow::nextRoundRequested,
        [&logicLayer]() {
            logicLayer.onStartNextRound();
        });

    connect(&mainWindow, &MainWindow::guessSubmitted,
        [&logicLayer](const geo::Point& guess) {
            logicLayer.onGuessSubmitted(guess);
        });

    // game -> ui
    Commands uiCommands;

    uiCommands.setMapCenter = [&mainWindow](const geo::Point& centerPoint){ mainWindow.setMapCenter(centerPoint); };
    uiCommands.startNextRound = [&mainWindow](const geo::Point& location){ mainWindow.startNextRound(location); };
    uiCommands.showPlayerGuessed = [&mainWindow](const std::string& playerName){ mainWindow.showPlayerGuessed(playerName); };
    uiCommands.showRoundResults = [&mainWindow](const game::RoundResults& roundResults){ mainWindow.showRoundResults(roundResults); };
    uiCommands.showErrorMessage = [&mainWindow](const std::string& what) {
        const QMessageBox::StandardButton bt = mainWindow.showErrorMessage(QString::fromStdString(what));
        return bt == QMessageBox::Retry ? ErrorAction::Retry : ErrorAction::Abort;
    };

    logicLayer.setUiCommands(std::move(uiCommands));
}

}
