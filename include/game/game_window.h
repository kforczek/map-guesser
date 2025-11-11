#pragma once
#include <QStackedLayout>
#include <QShortcut>

#include "streetview/distance_map.h"
#include "pages/round_results.h"
#include "pages/street_view.h"
#include "db/location_pool.h"

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

    pages::StreetViewPage m_streetViewPage;
    pages::RoundResultsPage m_roundResultsPage;

    QShortcut m_escShortcut;
    QShortcut m_f11Shortcut;

private /*methods*/:
    void startNextRound();
    void toggleFullScreen(std::optional<bool> fullScreen = std::nullopt);

private slots:
    void onGuessMade(const geo::Location& guessedLocation);
    void onContinueButtonClicked();
};

}
