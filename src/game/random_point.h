#pragma once
#include "geo/point.h"

namespace planar
{
class Map;
}

namespace game
{

geo::Point GetRandomStreetViewPoint(const planar::Map& projectedMap);

}