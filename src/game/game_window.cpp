#include "game/game_window.h"
#include "streetview/streetview.h"

#include <QFrame>
#include <QStackedLayout>

namespace game
{

GameWindow::GameWindow(const geo::Location& mapCenter)
    : m_layout(this)
    , m_streetViewPage(this, mapCenter)
    , m_roundResultsPage(this)
{
    setLayout(&m_layout);

    m_layout.addWidget(&m_streetViewPage);
    m_layout.addWidget(&m_roundResultsPage);

    m_layout.setCurrentIndex(0);

    connect(&m_streetViewPage, &pages::StreetViewPage::guessMade, this, &GameWindow::onGuessMade);
}


void GameWindow::setStreetViewLocation(const geo::Location& location)
{
    m_streetViewPage.setStreetViewLocation(location);
}

void GameWindow::onGuessMade(const geo::Location& guessedLocation)
{
    const geo::Location& actualLocation = m_streetViewPage.getStreetViewLocation();

    m_roundResultsPage.setActualLocation(actualLocation);
    m_roundResultsPage.setGuessedLocation(guessedLocation);

    m_layout.setCurrentIndex(1);
}

}
