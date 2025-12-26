#pragma once
#include <QWebChannel>
#include <QWebEngineView>

#include "polygon_map_bridge.h"

namespace geo
{
class Point;
}

namespace google
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
    QWebChannel m_channel;
    PolygonMapBridge m_bridge;

    void initBridge();
    void resetHtmlContent(const geo::Point& startLocation);
};

}
