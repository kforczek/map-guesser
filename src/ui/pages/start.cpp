#include "ui/pages/start.h"

#include <qboxlayout.h>
#include <QPushButton>

namespace
{

constinit QSize GAMEPLAY_BUTTON_SIZE{750, 90};
const QString GAMEPLAY_BUTTON_STYLE = "font-family: 'Segoe UI'; font-size: 30px; font-weight: bold";

constinit QSize EXTRA_BUTTON_SIZE{200, 70};
const QString EXTRA_BUTTON_STYLE = "font-family: 'Segoe UI'; font-size: 20px";

}

namespace ui::pages
{

StartPage::StartPage(QWidget* parent)
    : QFrame(parent)
{
    auto* layout = new QVBoxLayout(this);
    setLayout(layout);

    layout->addStretch(3);
    addGameplayButtons(*layout);
    layout->addStretch(2);
    addExtraButtons(*layout);
    layout->addStretch(1);
}

void StartPage::addGameplayButtons(QVBoxLayout& layout)
{
    auto* singlePlayerButton = new QPushButton("SINGLEPLAYER", this);
    auto* multiPlayerButton = new QPushButton("[coming soon] MULTIPLAYER", this);

    multiPlayerButton->setEnabled(false);

    singlePlayerButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    multiPlayerButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    singlePlayerButton->setProperty("role", "singleplayer");
    multiPlayerButton->setProperty("role", "multiplayer");

    singlePlayerButton->setFixedSize(GAMEPLAY_BUTTON_SIZE);
    multiPlayerButton->setFixedSize(GAMEPLAY_BUTTON_SIZE);

    singlePlayerButton->setStyleSheet(GAMEPLAY_BUTTON_STYLE);
    multiPlayerButton->setStyleSheet(GAMEPLAY_BUTTON_STYLE);

    layout.addWidget(singlePlayerButton, 0, Qt::AlignHCenter);
    layout.addSpacing(50);
    layout.addWidget(multiPlayerButton, 0, Qt::AlignHCenter);

    connect(singlePlayerButton, &QPushButton::clicked, this, &StartPage::singlePlayerRequested);
}

void StartPage::addExtraButtons(QVBoxLayout& layout)
{
    auto* bottomBarLayout = new QHBoxLayout;
    layout.addLayout(bottomBarLayout);

    auto* settingsButton = new QPushButton("Settings", this);
    settingsButton->setFixedSize(EXTRA_BUTTON_SIZE);
    settingsButton->setStyleSheet(EXTRA_BUTTON_STYLE);

    auto* mapEditorButton = new QPushButton("Map Editor", this);
    mapEditorButton->setFixedSize(EXTRA_BUTTON_SIZE);
    mapEditorButton->setStyleSheet(EXTRA_BUTTON_STYLE);

    bottomBarLayout->addWidget(settingsButton);
    bottomBarLayout->addSpacing(300);
    bottomBarLayout->addWidget(mapEditorButton);

    connect(mapEditorButton, &QPushButton::clicked, this, &StartPage::mapEditorRequested);
}

}