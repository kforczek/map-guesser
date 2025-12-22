#pragma once
#include "geo/point.h"

namespace db
{
class LocationPool;
}

namespace game
{

geo::Point GetRandomStreetViewPoint(const db::LocationPool& locPool);

}
