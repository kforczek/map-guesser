#pragma once
#include <QFrame>
#include <QStackedLayout>
#include <QShortcut>

#include "game/session.h"
#include "ui/pages/game_setup.h"
#include "ui/pages/start.h"
#include "ui/pages/round_results.h"
#include "ui/pages/street_view.h"
#include "ui/pages/map_editor.h"

namespace game
{

class MainWindow final : public QFrame
{
    Q_OBJECT
public:
    explicit MainWindow();

private /*fields*/:
    QStackedLayout m_layout;

    std::optional<Session> m_gameSession;

    ui::pages::StartPage m_startPage;
    ui::pages::GameSetupPage m_gameSetupPage;
    ui::pages::StreetViewPage m_streetViewPage;
    ui::pages::RoundResultsPage m_roundResultsPage;
    ui::pages::MapEditorPage m_mapEditorPage;

    QShortcut m_escShortcut;
    QShortcut m_f11Shortcut;

private /*methods*/:
    void initWindowProperties();
    void initLayoutPages();
    void initConnections();

    void startNextRound();
    void toggleFullScreen(std::optional<bool> fullScreen = std::nullopt);

private slots:
    // Go back to start - from multiple pages
    void onStartPageRequested();

    // Start page
    void onSinglePlayerRequested();
    void onMapEditorRequested();

    // Single/multiplayer pages
    void onStartGameRequested(util::Consumable<game::Params> gameParams);

    // Street view page
    void onGuessMade(const geo::Point& guessedLocation);
};

}
