#include "google/interactive_map_bridge.h"

namespace google
{

const std::optional<geo::Location>& InteractiveMapBridge::location() const
{
    return m_currLocation;
}

void InteractiveMapBridge::removeLocationMarker()
{
    emit markerRemoveRequest();
}

void InteractiveMapBridge::onCoordsChanged(double lat, double lng)
{
    m_currLocation = geo::Location{lat, lng};
    emit locationSet();
}

}
