#include "interactive_map_bridge.h"

namespace ui::google
{

const std::optional<geo::Point>& InteractiveMapBridge::location() const
{
    return m_currLocation;
}

void InteractiveMapBridge::removeLocationMarker()
{
    emit markerRemoveRequest();
}

void InteractiveMapBridge::onCoordsChanged(double lat, double lng)
{
    m_currLocation = geo::Point{lat, lng, geo::UnitType::Degrees};
    emit locationSet();
}

}
