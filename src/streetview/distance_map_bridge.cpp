#include "streetview/distance_updater.h"
#include "geo/location.h"

namespace sv
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
