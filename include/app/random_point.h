#pragma once
#include "geo/point.h"

namespace planar
{
class Map;
}

namespace app
{

geo::Point GetRandomStreetViewPoint(const planar::Map& projectedMap);

}