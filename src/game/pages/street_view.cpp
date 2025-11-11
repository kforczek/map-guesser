#include "game/pages/street_view.h"

namespace game::pages
{

StreetViewPage::StreetViewPage(QWidget* parent, const geo::Location& mapCenter)
    : QFrame(parent)
    , m_streetView(this)
    , m_interactiveMap(this, mapCenter)
    , m_guessButton("Guess", this)
{
    // TODO remove fixed sizes
    setContentsMargins(0, 0, 0, 0);

    m_streetView.setGeometry(rect());
    m_interactiveMap.setMinimumSize(400, 300);
    m_guessButton.setMinimumSize(100, 40);

    m_guessButton.setEnabled(false);

    connect(&m_interactiveMap, &sv::InteractiveMap::guessMarkerPlaced, this, &StreetViewPage::onGuessMarkerPlaced);
    connect(&m_guessButton, &QPushButton::clicked, this, &StreetViewPage::onGuessButtonClicked);
}

void StreetViewPage::setStreetViewLocation(const geo::Location& location)
{
    m_streetView.setLocation(location);
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

}