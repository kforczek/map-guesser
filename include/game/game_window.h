#pragma once
#include <QStackedLayout>
#include <QShortcut>

#include "google/distance_map.h"
#include "pages/start.h"
#include "pages/round_results.h"
#include "pages/street_view.h"
#include "db/location_pool.h"
#include "pages/map_editor.h"

namespace game
{

class GameWindow final : public QFrame
{
    Q_OBJECT
public:
    explicit GameWindow(db::LocationPool locPool);

private /*members*/:
    db::LocationPool m_locPool;
    QStackedLayout m_layout;

    pages::StartPage m_startPage;
    pages::StreetViewPage m_streetViewPage;
    pages::RoundResultsPage m_roundResultsPage;
    pages::MapEditorPage m_mapEditorPage;

    QShortcut m_escShortcut;
    QShortcut m_f11Shortcut;

private /*methods*/:
    void initWindowProperties();
    void initLayoutPages();
    void initConnections();

    void startNextRound();
    void toggleFullScreen(std::optional<bool> fullScreen = std::nullopt);

private slots:
    void onSinglePlayerSelected();
    void onMapEditorLaunched();

    void onGuessMade(const geo::Location& guessedLocation);
    void onContinueButtonClicked();
};

}
