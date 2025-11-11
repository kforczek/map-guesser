#pragma once
#include <QStackedLayout>

#include "streetview/distance_map.h"
#include "pages/round_results.h"
#include "pages/street_view.h"
#include "db/location_pool.h"

namespace game
{

class GameWindow : public QFrame
{
    Q_OBJECT
public:
    explicit GameWindow(db::LocationPool locPool);

private /*members*/:
    db::LocationPool m_locPool;
    QStackedLayout m_layout;

    pages::StreetViewPage m_streetViewPage;
    pages::RoundResultsPage m_roundResultsPage;

private /*methods*/:
    void startNextRound();

private slots:
    void onGuessMade(const geo::Location& guessedLocation);
    void onContinueButtonClicked();
};

}
