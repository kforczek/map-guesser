#pragma once
#include <iostream>
#include <QObject>
#include <optional>
#include "geo/point.h"

namespace ui::google
{

class InteractiveMapBridge final : public QObject
{
    Q_OBJECT

public:
    using QObject::QObject;

    void setCenter(const geo::Point& center);

    const std::optional<geo::Point>& location() const;
    void removeLocationMarker();

signals:
    // bridge -> js
    void updateCenter(double lat, double lng);
    void markerRemoveRequest();

    // bridge -> backend
    void locationSet();

public slots:
    void onHtmlReady();
    void onCoordsChanged(double lat, double lng);

private:
    bool m_htmlReady = false;
    geo::Point m_center;
    std::optional<geo::Point> m_currLocation;
};

}
