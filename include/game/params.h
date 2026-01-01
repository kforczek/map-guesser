#pragma once
#include "geo/map.h"
#include "planar/map.h"

namespace game
{

struct Params
{
    geo::Point geoCenter;
    planar::Map projectedMap;
};

}
