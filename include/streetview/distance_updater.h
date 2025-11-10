#pragma once
#include <QObject>

namespace geo
{
class Location;
}

namespace sv
{

class DistanceUpdater : public QObject {
    Q_OBJECT
public:
    using QObject::QObject;

public slots:
    void setMarkerA(const geo::Location& location);
    void setMarkerB(const geo::Location& location);

signals:
    void updateMarkerA(double lat, double lng);
    void updateMarkerB(double lat, double lng);
};


}