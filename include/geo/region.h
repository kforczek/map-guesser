#pragma once
#include "point.h"

namespace geo
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
