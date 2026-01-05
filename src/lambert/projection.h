#pragma once
#include "geo/point.h"
#include "planar/map.h"
#include "planar/region.h"
#include "planar/point.h"

namespace geo
{
class Point;
class Region;
class Map;
}

namespace lambert
{

/* Lambert Cylindrical Equal-Area Projection - conversions between geographic data (lat, lng)
 * and projected planar (x, y). Necessary for fair uniform selection of a random point from user's map. */

planar::Map project(const geo::Map& map);
planar::Region project(const geo::Region& region);
planar::Point project(const geo::Point& point);

geo::Point unproject(const planar::Point& point);

}
