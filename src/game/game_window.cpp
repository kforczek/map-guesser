#include "game/game_window.h"
#include "streetview/streetview.h"

#include <QFrame>
#include <QStackedLayout>

#include "db/location_pool.h"
#include "game/results.h"

namespace
{

constexpr short int PAGE_STREET_VIEW = 0;
constexpr short int PAGE_ROUND_RESULTS = 1;

}

namespace game
{

GameWindow::GameWindow(db::LocationPool locPool)
    : m_locPool(std::move(locPool))
    , m_layout(this)
    , m_streetViewPage(this, m_locPool.center())
    , m_roundResultsPage(this, m_locPool.center())
{
    setLayout(&m_layout);
    setMinimumSize(1000, 800);
    setWindowTitle("Map Guesser");

    m_layout.addWidget(&m_streetViewPage);
    m_layout.addWidget(&m_roundResultsPage);

    m_layout.setCurrentIndex(PAGE_STREET_VIEW);

    connect(&m_streetViewPage, &pages::StreetViewPage::guessMade, this, &GameWindow::onGuessMade);
}


void GameWindow::setStreetViewLocation(const geo::Location& location)
{
    m_streetViewPage.setStreetViewLocation(location);
}

void GameWindow::onGuessMade(const geo::Location& guessedLocation)
{
    const geo::Location& actualLocation = m_streetViewPage.getStreetViewLocation();
    const RoundResults roundResults{m_locPool, actualLocation, guessedLocation};

    m_roundResultsPage.setActualLocation(actualLocation);
    m_roundResultsPage.setGuessedLocation(guessedLocation);
    m_roundResultsPage.setInfo(roundResults);

    m_layout.setCurrentIndex(PAGE_ROUND_RESULTS);
}

}
