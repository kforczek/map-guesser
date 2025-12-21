#include "game/pages/start.h"

namespace game::pages
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

    m_layout.addWidget(&m_singlePlayerButton);
    m_layout.addWidget(&m_multiPlayerButton);
    m_layout.addWidget(&m_mapEditorButton);

    connect(&m_singlePlayerButton, &QPushButton::clicked, [this](){ emit singlePlayerButtonClicked(); });
    connect(&m_mapEditorButton, &QPushButton::clicked, [this](){ emit mapEditorButtonClicked(); });
}

}