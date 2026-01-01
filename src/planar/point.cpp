#include "planar/point.h"

namespace planar
{

Point::Point(double x, double y)
    : m_x(x)
    , m_y(y) { }

double Point::x() const
{
    return m_x;
}

double Point::y() const
{
    return m_y;
}

}