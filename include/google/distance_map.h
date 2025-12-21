#pragma once
#include <QWebChannel>
#include <QWebEngineView>

#include "distance_map_bridge.h"

namespace geo
{
class Location;
}

namespace google
{

class DistanceMap : public QWebEngineView
{
public:
    explicit DistanceMap(QWidget* parent, const geo::Location& mapCenter);

    void setActualLocation(const geo::Location& location);
    void setGuessedLocation(const geo::Location& location);
    void setDistance(double distance);

private:
    QWebChannel m_channel;
    DistanceMapBridge m_bridge;

    void initBridge();
    void initHtmlContent(const geo::Location& mapCenter);
};

}
