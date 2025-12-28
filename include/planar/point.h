#pragma once
#include "geo/point.h"

namespace planar
{

/* Point projected to plane (Equal-area projection) */
class Point
{
    Point(double x, double y);

    static Point project(const geo::Point& point);
    geo::Point unproject() const;

    double x() const;
    double y() const;

private:
    double m_x = 0;
    double m_y = 0;
};

}