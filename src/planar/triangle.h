#pragma once
#include "point.h"

namespace planar
{

class Triangle
{
public:
    Triangle(Point a, Point b, Point c);

    double area() const;

    Point getRandomPoint() const;

private:
    Point m_a;
    Point m_b;
    Point m_c;

    double m_area = 0;
};

}
