#pragma once
#include <QWebChannel>
#include <QWebEngineView>

#include "polygon_map_bridge.h"

namespace geo
{
class Location;
}

namespace google
{

class PolygonMap final : public QWebEngineView
{
    Q_OBJECT
public:
    PolygonMap(QWidget* parent);

private:
    QWebChannel m_channel;
    PolygonMapBridge m_bridge;

    void initBridge();
    void resetHtmlContent(const geo::Location& startLocation);
};

}
