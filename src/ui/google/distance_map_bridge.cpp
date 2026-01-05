#include "distance_map_bridge.h"
#include "geo/point.h"

namespace ui::google
{

void DistanceMapBridge::setMarkerActual(const geo::Point& location)
{
    emit updateMarkerActual(location.latitude(), location.longitude());
}

void DistanceMapBridge::setMarkerGuessed(const geo::Point& location)
{
    emit updateMarkerGuessed(location.latitude(), location.longitude());
}

void DistanceMapBridge::setDistance(const double distance)
{
    emit updateDistance(distance);
}

}
