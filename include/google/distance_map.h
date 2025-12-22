#pragma once
#include <QWebChannel>
#include <QWebEngineView>

#include "distance_map_bridge.h"

namespace geo
{
class Point;
}

namespace google
{

class DistanceMap : public QWebEngineView
{
public:
    explicit DistanceMap(QWidget* parent, const geo::Point& mapCenter);

    void setActualLocation(const geo::Point& location);
    void setGuessedLocation(const geo::Point& location);
    void setDistance(double distance);

private:
    QWebChannel m_channel;
    DistanceMapBridge m_bridge;

    void initBridge();
    void initHtmlContent(const geo::Point& mapCenter);
};

}
