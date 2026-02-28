#include "interactive_map_bridge.h"

namespace ui::google
{

void InteractiveMapBridge::setCenter(const geo::Point& center)
{
    m_center = center;

    if (m_htmlReady)
        emit updateCenter(m_center.latitude(), m_center.longitude());
}

const std::optional<geo::Point>& InteractiveMapBridge::location() const
{
    return m_currLocation;
}

void InteractiveMapBridge::removeLocationMarker()
{
    emit markerRemoveRequest();
}

void InteractiveMapBridge::onHtmlReady()
{
    m_htmlReady = true;

    if (m_center != geo::Point{})
        emit updateCenter(m_center.latitude(), m_center.longitude());
}

void InteractiveMapBridge::onCoordsChanged(double lat, double lng)
{
    m_currLocation = geo::Point{lat, lng, geo::UnitType::Degrees};
    emit locationSet();
}

}
