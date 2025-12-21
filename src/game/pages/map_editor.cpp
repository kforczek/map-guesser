#include "game/pages/map_editor.h"

namespace game::pages
{

MapEditorPage::MapEditorPage(QWidget* parent)
    : QFrame(parent)
    , m_topBar(this)
    , m_map(this)
{
    setLayout(&m_layout);

    m_layout.addWidget(&m_topBar);
    m_layout.addWidget(&m_map);
}

}