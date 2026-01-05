#pragma once
#include "geo/map.h"
#include "planar/map.h"

namespace game
{

struct Params
{
    geo::Map geoMap;
    planar::Map projectedMap;

    unsigned int maxRoundPoints = 0;
};

}
