#pragma once
#include <QWebEngineView>

#include "polygon_map_bridge.h"

namespace geo
{
class Point;
}

namespace ui::google
{

class PolygonMap final : public QWebEngineView
{
    Q_OBJECT
public:
    explicit PolygonMap(QWidget* parent);

    void loadMap(const geo::Map& map);

signals:
    void mapChanged(util::Consumable<geo::Map> updatedMap);

private:
    PolygonMapBridge* m_bridge = nullptr;

    void initBridge();
    void resetHtmlContent(const geo::Point& startLocation);
};

}
