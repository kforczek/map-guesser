#include "streetview/distance_updater.h"

#include "geo/location.h"

namespace sv
{

void DistanceUpdater::setMarkerA(const geo::Location& location)
{
    emit updateMarkerA(location.latitude(), location.longitude());
}

void DistanceUpdater::setMarkerB(const geo::Location& location)
{
    emit updateMarkerB(location.latitude(), location.longitude());
}

}
