#pragma once
#include "point.h"

namespace geo
{

class Region
{
public:
    explicit Region(std::vector<Point> points);

private:
    std::vector<Point> m_points;
};

}
