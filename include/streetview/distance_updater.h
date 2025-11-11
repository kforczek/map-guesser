#pragma once
#include <QObject>

namespace geo
{
class Location;
}

namespace sv
{

class DistanceMapBridge : public QObject {
    Q_OBJECT
public:
    using QObject::QObject;

public slots:
    void setMarkerActual(const geo::Location& location);
    void setMarkerGuessed(const geo::Location& location);
    void setDistance(double distance);

signals:
    void updateMarkerActual(double lat, double lng);
    void updateMarkerGuessed(double lat, double lng);
    void updateDistance(double distance);
};


}