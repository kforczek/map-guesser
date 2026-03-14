#pragma once
#include <QFrame>
#include <QMessageBox>

#include "geo/point.h"

class QStackedLayout;
class QShortcut;

namespace game
{
class RoundResults;
struct Params;
}

namespace ui
{

namespace pages
{
class StartPage;
class GameSetupPage;
class GameplayPage;
class RoundResultsPage;
class GhostWalkPage;
class SummaryPage;
class MapEditorPage;
class SettingsPage;
}

class MainWindow final : public QFrame
{
    Q_OBJECT
public:
    explicit MainWindow();

    void setMapCenter(const geo::Point& centerPoint);
    void startNextRound(const geo::Point& location);
    void showPlayerGuessed(const std::string& playerName);
    void showRoundResults(const game::RoundResults& roundResults, bool isGameOver);
    void showGameSummary(
        const std::vector<std::string>& leaderboard,
        const std::vector<game::RoundResults>& roundsHistory,
        int initialPoints
    );

    QMessageBox::StandardButton showErrorMessage(QString errDetails);

signals:
    void startGameRequested(std::shared_ptr<game::Params> gameParams);
    void guessSubmitted(const geo::Point& guessedLocation);
    void nextRoundRequested();

private /*fields*/:
    QStackedLayout* m_layout = nullptr;

    pages::StartPage* m_startPage = nullptr;
    pages::GameSetupPage* m_gameSetupPage = nullptr;
    pages::GameplayPage* m_gameplayPage = nullptr;
    pages::RoundResultsPage* m_roundResultsPage = nullptr;
    pages::GhostWalkPage* m_ghostWalkPage = nullptr;
    pages::SummaryPage* m_summaryPage = nullptr;
    pages::MapEditorPage* m_mapEditorPage = nullptr;
    pages::SettingsPage* m_settingsPage = nullptr;

    QShortcut* m_escShortcut = nullptr;
    QShortcut* m_f11Shortcut = nullptr;

    geo::Point m_currentLocation;

private /*methods*/:
    void initWindowProperties();
    void initLayoutPagesStackup();
    void initConnections();

    void toggleFullScreen(std::optional<bool> fullScreen = std::nullopt);

private slots:
    // Go back to start - from multiple pages
    void onStartPageRequested();

    // Start page
    void onSinglePlayerRequested();
    void onMapEditorRequested();
    void onSettingsRequested();

    // Round results page
    void onGhostWalkEnterRequested();

    // Ghost walk page
    void onGhostWalkExitRequested();
};

}
