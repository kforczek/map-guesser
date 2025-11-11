#include "streetview/distance_updater.h"

#include "geo/location.h"

namespace sv
{

void DistanceUpdater::setMarkerActual(const geo::Location& location)
{
    emit updateMarkerActual(location.latitude(), location.longitude());
}

void DistanceUpdater::setMarkerGuessed(const geo::Location& location)
{
    emit updateMarkerGuessed(location.latitude(), location.longitude());
}

}
