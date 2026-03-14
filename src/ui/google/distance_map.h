#pragma once
#include <QWebChannel>
#include <QWebEngineView>

#include "distance_map_bridge.h"

namespace geo
{
class Point;
}

namespace ui::api_usage
{
class Counter;
}

namespace ui::google
{

class DistanceMap final : public QWebEngineView
{
public:
    explicit DistanceMap(QWidget* parent, api_usage::Counter& counter);

    void setCenter(const geo::Point& center);

    void setActualLocation(const geo::Point& location);
    void setGuessedLocation(const geo::Point& location);
    void setDistance(double distance);

private:
    DistanceMapBridge* m_bridge = nullptr;

    bool tryIncreaseApiCounter(api_usage::Counter& counter);

    void initBridge();
    void initHtmlContent();
};

}
