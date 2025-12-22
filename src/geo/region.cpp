#include "geo/region.h"

namespace geo
{

Region::Region(std::vector<Point> points)
    : m_points(std::move(points))
{
}

}