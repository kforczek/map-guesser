#pragma once
#include <iostream>
#include <QObject>
#include <optional>
#include "geo/point.h"

namespace google
{

class InteractiveMapBridge : public QObject
{
    Q_OBJECT

public:
    using QObject::QObject;

    const std::optional<geo::Point>& location() const;
    void removeLocationMarker();

signals:
    void locationSet();
    void markerRemoveRequest();

public slots:
    void onCoordsChanged(double lat, double lng);

private:
    std::optional<geo::Point> m_currLocation;
};

}
