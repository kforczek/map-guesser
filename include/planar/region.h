#pragma once
#include <vector>
#include "point.h"

namespace planar
{

class Region
{
public:
    explicit Region(std::vector<Point> points);

    const std::vector<Point>& points() const;

private:
    std::vector<Point> m_points;
};

}