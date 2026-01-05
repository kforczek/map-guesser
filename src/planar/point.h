#pragma once

namespace planar
{

/* Point projected to plane */
class Point
{
public:
    Point(double x, double y);

    double x() const;
    double y() const;

private:
    double m_x = 0;
    double m_y = 0;
};

}