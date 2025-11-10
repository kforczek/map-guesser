#pragma once
#include <QWebChannel>
#include <QWebEngineView>

#include "distance_updater.h"

namespace geo
{
class Location;
}

namespace sv
{

class DistanceMap : public QWebEngineView
{
public:
    DistanceMap(QWidget* parent = nullptr);

    void setPointA(const geo::Location& location);
    void setPointB(const geo::Location& location);

private:
    QWebChannel m_channel;
    DistanceUpdater m_distanceUpdater;

    void initDistanceConnector();
    void initHtmlContent();
};

}
