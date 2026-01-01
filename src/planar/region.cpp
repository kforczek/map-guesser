#include "planar/region.h"

namespace planar
{

Region::Region(std::vector<Point> points)
    : m_points(std::move(points)) { }

const std::vector<Point>& Region::points() const
{
    return m_points;
}

}