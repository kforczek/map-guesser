#pragma once
#include <QStackedLayout>

#include "streetview/distance_map.h"
#include "geo/location.h"
#include "pages/round_results.h"
#include "pages/street_view.h"

namespace game
{

class GameWindow : public QFrame
{
    Q_OBJECT
public:
    explicit GameWindow(const geo::Location& mapCenter);

    void setStreetViewLocation(const geo::Location& location);

private /*members*/:
    QStackedLayout m_layout;

    pages::StreetViewPage m_streetViewPage;
    pages::RoundResultsPage m_roundResultsPage;

private slots:
    void onGuessMade(const geo::Location& guessedLocation);
};

}
