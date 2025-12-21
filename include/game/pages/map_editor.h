#pragma once
#include <qboxlayout.h>
#include <QFrame>

#include "google/polygon_map.h"
#include "mapeditor/top_bar.h"

namespace game::pages
{

class MapEditorPage final : public QFrame
{
    Q_OBJECT
public:
    explicit MapEditorPage(QWidget* parent);

private:
    QVBoxLayout m_layout;

    mapeditor::TopBar m_topBar;
    google::PolygonMap m_map;
};

}
