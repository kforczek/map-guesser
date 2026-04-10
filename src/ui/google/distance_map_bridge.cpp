#include "distance_map_bridge.h"

#include <qvariant.h>

namespace
{

QVariant getLatitude(const std::optional<geo::Point>& point)
{
    return point ? QVariant::fromValue(point->latitude()) : QVariant();
}

QVariant getLongitude(const std::optional<geo::Point>& point)
{
    return point ? QVariant::fromValue(point->longitude()) : QVariant();
}

}

namespace ui::google
{

void DistanceMapBridge::setCenter(const geo::Point& location)
{
    m_center = location;

    if (m_htmlReady)
        emit updateCenter(m_center.latitude(), m_center.longitude());
}

void DistanceMapBridge::setMarkerActual(const geo::Point& location)
{
    m_markerActual = location;

    if (m_htmlReady)
        emit updateMarkerActual(m_markerActual.latitude(), m_markerActual.longitude());
}

void DistanceMapBridge::setMarkerGuessed(const std::optional<geo::Point>& location)
{
    m_markerGuessed = location;

    if (m_htmlReady)
        emit updateMarkerGuessed(getLatitude(m_markerGuessed), getLongitude(m_markerGuessed));
}

void DistanceMapBridge::setDistance(double distance)
{
    m_distance = distance;

    if (m_htmlReady)
        emit updateDistance(m_distance);
}

void DistanceMapBridge::onHtmlReady()
{
    m_htmlReady = true;

    if (m_center != geo::Point{})
        emit updateCenter(m_center.latitude(), m_center.longitude());

    if (m_markerActual != geo::Point{})
        emit updateMarkerActual(m_markerActual.latitude(), m_markerActual.longitude());

    if (m_markerGuessed.has_value())
        emit updateMarkerGuessed(getLatitude(m_markerGuessed), getLongitude(m_markerGuessed));

    if (m_distance != 0)
        emit updateDistance(m_distance);
}


}
