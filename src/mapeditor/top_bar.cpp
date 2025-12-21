#include "mapeditor/top_bar.h"

namespace mapeditor
{

TopBar::TopBar(QWidget* parent)
    : QWidget(parent)
    , m_layout(this)
    , m_infoLabel("Map: Untitled", this)
    , m_loadButton("Load", this)
    , m_saveAsButton("Save As...", this)
{
    setLayout(&m_layout);

    m_infoLabel.setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);

    m_layout.addWidget(&m_infoLabel);
    m_layout.addWidget(&m_loadButton);
    m_layout.addWidget(&m_saveAsButton);
}

}