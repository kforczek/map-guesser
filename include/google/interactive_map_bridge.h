#pragma once
#include <iostream>
#include <QObject>
#include <optional>
#include "geo/location.h"

namespace google
{

class InteractiveMapBridge : public QObject
{
    Q_OBJECT

public:
    using QObject::QObject;

    const std::optional<geo::Location>& location() const;
    void removeLocationMarker();

signals:
    void locationSet();
    void markerRemoveRequest();

public slots:
    void onCoordsChanged(double lat, double lng);

private:
    std::optional<geo::Location> m_currLocation;
};

}
