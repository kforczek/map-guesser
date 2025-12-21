#include "google/distance_map_bridge.h"
#include "geo/location.h"

namespace google
{

void DistanceMapBridge::setMarkerActual(const geo::Location& location)
{
    emit updateMarkerActual(location.latitude(), location.longitude());
}

void DistanceMapBridge::setMarkerGuessed(const geo::Location& location)
{
    emit updateMarkerGuessed(location.latitude(), location.longitude());
}

void DistanceMapBridge::setDistance(const double distance)
{
    emit updateDistance(distance);
}

}
