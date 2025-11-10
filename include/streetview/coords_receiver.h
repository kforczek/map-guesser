#pragma once
#include <iostream>
#include <QObject>
#include <optional>
#include "geo/location.h"

namespace sv
{

class CoordsReceiver : public QObject
{
    Q_OBJECT

public:
    using QObject::QObject;

    const std::optional<geo::Location>& location() const;

public slots:
    void onCoordsChanged(double lat, double lng);

private:
    std::optional<geo::Location> m_currLocation;
};

}
