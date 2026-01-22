#pragma once
#include "defs.h"
#include "geo/point.h"

namespace game::engine
{

struct ActiveRound
{
    geo::Point correctLocation;
    TPlayer2Guess guesses;
};

}
