#include "game/game_window.h"
#include "streetview/streetview.h"

#include <QFrame>
#include <QStackedLayout>

namespace game
{

GameWindow::GameWindow(const geo::Location& mapStartLocation)
    : m_streetView(this)
    , m_interactiveMap(this, mapStartLocation)
{
    setFixedSize(1000, 800);

    auto* container = new QFrame(this);
    container->setContentsMargins(0, 0, 0, 0);
    container->setLayout(new QStackedLayout(container));
    setCentralWidget(container);

    container->layout()->addWidget(&m_streetView);

    m_interactiveMap.setFixedSize(400, 300);
    m_interactiveMap.move(width() - m_interactiveMap.width() - 10,
                         height() - m_interactiveMap.height() - 10);
    m_interactiveMap.raise();

    m_interactiveMap.setMouseTracking(true);
    //container->installEventFilter(this);
}

void GameWindow::setLocation(const geo::Location& location)
{
    m_streetView.setLocation(location);
}

}
