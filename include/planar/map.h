#pragma once
#include "point.h"

namespace geo
{
class Map;
}

namespace planar
{

class Map
{
public:
    static Map fromGeoMap(const geo::Map& geoMap);

    //Point getRandomPoint...();

private:
    //Map(...)
};

}
