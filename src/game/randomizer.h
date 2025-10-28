#pragma once
#include "db/location_pool.h"

namespace db
{
class LocationPool;
}

namespace geo
{
class Location;
}

namespace game
{

geo::Location GetRandomStreetViewPoint(const db::LocationPool& locPool);

}
