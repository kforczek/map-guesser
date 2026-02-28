#pragma once
#include <QObject>
#include "geo/point.h"

namespace ui::google
{

class DistanceMapBridge final : public QObject
{
    Q_OBJECT
public:
    using QObject::QObject;

    void setCenter(const geo::Point& center);
    void setMarkerActual(const geo::Point& location);
    void setMarkerGuessed(const geo::Point& location);
    void setDistance(double distance);

public slots:
    void onHtmlReady();

signals:
    void updateCenter(double lat, double lng);
    void updateMarkerActual(double lat, double lng);
    void updateMarkerGuessed(double lat, double lng);
    void updateDistance(double distance);

private:
    bool m_htmlReady = false;

    geo::Point m_center;
    geo::Point m_markerActual;
    geo::Point m_markerGuessed;
    double m_distance = 0;
};


}