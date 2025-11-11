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
    explicit DistanceMap(QWidget* parent = nullptr);

    void setActualLocation(const geo::Location& location);
    void setGuessedLocation(const geo::Location& location);

private:
    QWebChannel m_channel;
    DistanceUpdater m_distanceUpdater;

    void initDistanceConnector();
    void initHtmlContent();
};

}
