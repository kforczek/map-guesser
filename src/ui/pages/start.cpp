#include "ui/pages/start.h"

namespace
{

void addButtonToLayout(QBoxLayout& layout, QPushButton& button)
{
    button.setFixedSize(QSize(750, 90));
    button.setStyleSheet("font-family: 'Segoe UI'; font-size: 30px; font-weight: bold");
    layout.addWidget(&button, 0, Qt::AlignHCenter);
}

}

namespace ui::pages
{

StartPage::StartPage(QWidget* parent)
    : QFrame(parent)
    , m_layout(this)
    , m_singlePlayerButton("SINGLEPLAYER", this)
    , m_spacer(0, 50)
    , m_multiPlayerButton("[coming soon] MULTIPLAYER", this)
    , m_bottomBar(this)
{
    setLayout(&m_layout);

    m_multiPlayerButton.setEnabled(false);

    m_singlePlayerButton.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_multiPlayerButton.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_singlePlayerButton.setProperty("role", "singleplayer");
    m_multiPlayerButton.setProperty("role", "multiplayer");

    m_layout.addStretch(3);
    addButtonToLayout(m_layout, m_singlePlayerButton);
    m_layout.addItem(&m_spacer);
    addButtonToLayout(m_layout, m_multiPlayerButton);
    m_layout.addStretch(2);
    m_layout.addWidget(&m_bottomBar);
    m_layout.addStretch(1);

    connect(&m_singlePlayerButton, &QPushButton::clicked, this, &StartPage::singlePlayerRequested);
    connect(&m_bottomBar, &widgets::StartPageBottomBar::mapEditorButtonClicked, this, &StartPage::mapEditorRequested);
}

}