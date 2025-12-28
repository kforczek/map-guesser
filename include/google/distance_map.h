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

class DistanceMap final : public QWebEngineView
{
public:
    explicit DistanceMap(QWidget* parent);

    void setActualLocation(const geo::Point& location);
    void setGuessedLocation(const geo::Point& location);
    void setDistance(double distance);

    void setCenter(const geo::Point& center);

private:
    QWebChannel m_channel;
    DistanceMapBridge m_bridge;

    void initBridge();
    void resetHtmlContent(const geo::Point& mapCenter);
};

}
