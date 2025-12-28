#pragma once
#include "geo/map.h"

namespace game
{

struct Params
{
    // TODO: perhaps save geo center() and planar::Map instead
    geo::Map map;
    // ...
};

}