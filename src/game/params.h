#pragma once
#include "geo/map.h"
#include "planar/map.h"

namespace game
{

// TODO: some params hierarchy, maybe factory or just variant here
struct Params
{
    geo::Map geoMap;
    planar::Map projectedMap;

    std::vector<std::string> playerNames;

    unsigned int roundsCnt = 0;
    unsigned int maxRoundPoints = 0;

    size_t playersCnt() const { return playerNames.size(); }
    const std::string& myPlayerName() const { return playerNames.front(); }
};

}
