#include "start_page_bottom_bar.h"

namespace ui::widgets
{

StartPageBottomBar::StartPageBottomBar(QWidget *parent)
    : QWidget(parent)
    , m_settingsButton("Settings", this)
    , m_mapEditorButton("Map Editor", this)
{
    setLayout(&m_layout);

    m_layout.addStretch();
    m_layout.addWidget(&m_settingsButton);
    m_layout.addStretch();
    m_layout.addWidget(&m_mapEditorButton);
    m_layout.addStretch();

    connect(&m_settingsButton, &QPushButton::clicked, this, &StartPageBottomBar::settingsButtonClicked);
    connect(&m_mapEditorButton, &QPushButton::clicked, this, &StartPageBottomBar::mapEditorButtonClicked);
}


}
