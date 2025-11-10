#pragma once
#include "geo/location.h"

namespace db
{
class LocationPool;
}

namespace game
{

geo::Location GetRandomStreetViewPoint(const db::LocationPool& locPool);

}
