#include "planar/region.h"

namespace planar
{

Region::Region(std::vector<Point> points)
    : m_points(std::move(points)) { }

}