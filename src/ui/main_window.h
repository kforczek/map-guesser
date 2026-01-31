#pragma once
#include <QFrame>
#include <QMessageBox>
#include <QStackedLayout>
#include <QShortcut>

#include "pages/game_setup.h"
#include "pages/start.h"
#include "pages/round_results.h"
#include "pages/street_view.h"
#include "pages/map_editor.h"

namespace ui
{

class MainWindow final : public QFrame
{
    Q_OBJECT
public:
    explicit MainWindow();

    void setMapCenter(const geo::Point& centerPoint);
    void startNextRound(const geo::Point& location);
    void showPlayerGuessed(const std::string& playerName);
    void showRoundResults(const game::RoundResults& roundResults);

    QMessageBox::StandardButton showErrorMessage(QString errDetails);

signals:
    void nextRoundRequested();
    void startGameRequested(std::shared_ptr<game::Params> gameParams);
    void guessSubmitted(const geo::Point& guessedLocation);

private /*fields*/:
    QStackedLayout m_layout;

    pages::StartPage m_startPage;
    pages::GameSetupPage m_gameSetupPage;
    pages::StreetViewPage m_streetViewPage;
    pages::RoundResultsPage m_roundResultsPage;
    pages::MapEditorPage m_mapEditorPage;

    QShortcut m_escShortcut;
    QShortcut m_f11Shortcut;

private /*methods*/:
    void initWindowProperties();
    void initLayoutPages();
    void initConnections();

    void toggleFullScreen(std::optional<bool> fullScreen = std::nullopt);

private slots:
    // Go back to start - from multiple pages
    void onStartPageRequested();

    // Start page
    void onSinglePlayerRequested();
    void onMapEditorRequested();
};

}
