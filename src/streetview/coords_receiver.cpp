#include "streetview/coords_receiver.h"

namespace sv
{

const std::optional<geo::Location>& CoordsReceiver::location() const
{
    return m_currLocation;
}

void CoordsReceiver::removeLocationMarker()
{
    emit markerRemoveRequest();
}

void CoordsReceiver::onCoordsChanged(double lat, double lng)
{
    m_currLocation = geo::Location{lat, lng};
    emit locationSet();
}

}
