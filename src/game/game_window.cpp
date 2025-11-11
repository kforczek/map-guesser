#include "game/game_window.h"
#include "streetview/streetview.h"

#include <QFrame>
#include <QStackedLayout>

namespace game
{

GameWindow::GameWindow(const geo::Location& mapStartLocation)
    : m_streetView(this)
    , m_interactiveMap(this, mapStartLocation)
    , m_distanceMap(this)
    , m_guessButton(new QPushButton("Guess", this))
{
    setFixedSize(1000, 800);

    auto* container = new QFrame(this);
    container->setContentsMargins(0, 0, 0, 0);
    auto* stacked = new QStackedLayout(container);
    container->setLayout(stacked);
    setCentralWidget(container);

    stacked->addWidget(&m_streetView);

    m_interactiveMap.setFixedSize(400, 300);
    m_interactiveMap.move(width() - m_interactiveMap.width() - 10,
                          height() - m_interactiveMap.height() - 50);
    m_interactiveMap.raise();
    m_interactiveMap.setMouseTracking(true);

    m_guessButton.setText("Guess");
    m_guessButton.setEnabled(false);
    m_guessButton.setParent(container);
    m_guessButton.setFixedSize(100, 40);
    m_guessButton.move(
        m_interactiveMap.x() + m_interactiveMap.width() - m_guessButton.width(),
        m_interactiveMap.y() + m_interactiveMap.height() + 5
    );
    m_guessButton.raise();

    m_distanceMap.setParent(container);
    m_distanceMap.setGeometry(container->rect());
    m_distanceMap.hide();
    m_distanceMap.raise();

    connect(&m_guessButton, &QPushButton::clicked, this, &GameWindow::onGuessButtonClicked);
    connect(&m_interactiveMap, &sv::InteractiveMap::locationSet, this, [this](){
        m_guessButton.setEnabled(true);
    });
}


void GameWindow::setLocation(geo::Location location)
{
    m_streetView.setLocation(location);
    m_currLocation = location;
}

void GameWindow::onGuessButtonClicked()
{
    const auto& guessedLocation = m_interactiveMap.currLocation();
    assert(guessedLocation);

    m_distanceMap.setPointA(m_currLocation);
    m_distanceMap.setPointB(*guessedLocation);

    m_distanceMap.setGeometry(centralWidget()->rect());
    m_distanceMap.show();

    m_streetView.hide();
    m_interactiveMap.hide();
    m_guessButton.hide();
}

}
