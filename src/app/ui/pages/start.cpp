#include "app/ui/pages/start.h"

namespace
{

void addButtonToLayout(QBoxLayout& layout, QPushButton& button)
{
    button.setFixedSize(QSize(600, 75));
    button.setStyleSheet("font-family: 'Segoe UI'; font-size: 30px; font-weight: bold");
    layout.addWidget(&button, 0, Qt::AlignHCenter);
}

}

namespace app::ui::pages
{

StartPage::StartPage(QWidget* parent)
    : QFrame(parent)
    , m_layout(this)
    , m_singlePlayerButton("SINGLEPLAYER", this)
    , m_multiPlayerButton("[coming soon] MULTIPLAYER", this)
    , m_mapEditorButton("Map Editor", this)
{
    setLayout(&m_layout);

    m_multiPlayerButton.setEnabled(false);

    m_singlePlayerButton.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_multiPlayerButton.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_layout.addStretch();
    addButtonToLayout(m_layout, m_singlePlayerButton);
    addButtonToLayout(m_layout, m_multiPlayerButton);
    m_layout.addStretch();
    m_layout.addWidget(&m_mapEditorButton);

    connect(&m_singlePlayerButton, &QPushButton::clicked, [this](){ emit singlePlayerButtonClicked(); });
    connect(&m_mapEditorButton, &QPushButton::clicked, [this](){ emit mapEditorButtonClicked(); });
}

}