#include "game/pages/street_view.h"

namespace game::pages
{

StreetViewPage::StreetViewPage(QWidget* parent, const geo::Location& mapCenter)
    : QFrame(parent)
    , m_streetView(this)
    , m_interactiveMap(this, mapCenter)
    , m_returnToStartButton("Return to start", this)
    , m_guessButton("Guess", this)
{
    setContentsMargins(0, 0, 0, 0);

    m_streetView.setGeometry(rect());
    m_interactiveMap.setMinimumSize(400, 300);
    m_guessButton.setMinimumSize(150, 40);
    m_returnToStartButton.setMinimumSize(150, 40);

    m_guessButton.setEnabled(false);

    connect(&m_interactiveMap, &sv::InteractiveMap::guessMarkerPlaced, this, &StreetViewPage::onGuessMarkerPlaced);
    connect(&m_guessButton, &QPushButton::clicked, this, &StreetViewPage::onGuessButtonClicked);
    connect(&m_returnToStartButton, &QPushButton::clicked, this, &StreetViewPage::onReturnToStartButtonClicked);
}

const geo::Location& StreetViewPage::getStreetViewLocation() const
{
    return m_streetView.getLocation();
}

void StreetViewPage::startNewRound(const geo::Location& location)
{
    m_streetView.setLocation(location);
    m_interactiveMap.removeLocationMarker();
    m_guessButton.setEnabled(false);
}

void StreetViewPage::resizeEvent(QResizeEvent* event)
{
    m_streetView.resize(width(), height());

    m_interactiveMap.move(width() - m_interactiveMap.width() - 10,
                            height() - m_interactiveMap.height() - 50);

    m_guessButton.move(
        m_interactiveMap.x() + m_interactiveMap.width() - m_guessButton.width(),
        m_interactiveMap.y() + m_interactiveMap.height() + 5
    );

    m_returnToStartButton.move(
        m_guessButton.x() - m_returnToStartButton.width() - 10,
        m_guessButton.y()
    );
}

void StreetViewPage::onGuessMarkerPlaced()
{
    m_guessButton.setEnabled(true);
}

void StreetViewPage::onGuessButtonClicked()
{
    const auto& guessedLocation = m_interactiveMap.currLocation();
    assert(guessedLocation);

    emit guessMade(*guessedLocation);
}

void StreetViewPage::onReturnToStartButtonClicked()
{
    m_streetView.returnToStart();
}

}