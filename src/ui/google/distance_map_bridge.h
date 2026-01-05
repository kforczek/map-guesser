#pragma once
#include <QObject>

namespace geo
{
class Point;
}

namespace ui::google
{

class DistanceMapBridge final : public QObject
{
    Q_OBJECT
public:
    using QObject::QObject;

public slots:
    void setMarkerActual(const geo::Point& location);
    void setMarkerGuessed(const geo::Point& location);
    void setDistance(double distance);

signals:
    void updateMarkerActual(double lat, double lng);
    void updateMarkerGuessed(double lat, double lng);
    void updateDistance(double distance);
};


}