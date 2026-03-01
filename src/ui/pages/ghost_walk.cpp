#include "ghost_walk.h"

#include <qboxlayout.h>
#include <QPushButton>

#include "ui/google/streetview.h"

namespace ui::pages
{

GhostWalkPage::GhostWalkPage(QWidget* parent)
    : QFrame(parent) { }

void GhostWalkPage::setLocation(const geo::Point& location)
{
    if (m_currLocation == location)
        return;

    ensureInitialized();

    m_currLocation = location;
    m_streetView->setLocation(location);
}

void GhostWalkPage::ensureInitialized()
{
    if (m_streetView)
        return;

    m_streetView = new google::StreetView(this);

    auto* layout = new QVBoxLayout(this);
    setLayout(layout);

    QMargins layoutMargins = layout->contentsMargins();
    layoutMargins.setLeft(0);
    layoutMargins.setRight(0);
    layout->setContentsMargins(layoutMargins);

    auto* exitButton = new QPushButton("Back", this);
    exitButton->setMinimumSize(100, 40);

    auto* bottomBar = new QHBoxLayout();
    bottomBar->setContentsMargins(10, 0, 0, 0);
    bottomBar->addWidget(exitButton);
    bottomBar->addStretch();

    layout->addWidget(m_streetView);
    layout->addLayout(bottomBar);

    connect(exitButton, &QPushButton::clicked, this, &GhostWalkPage::closePage);
}

}
