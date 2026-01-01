#include "planar/triangle.h"

#include <cmath>
#include <random>

namespace
{

using namespace planar;

std::mt19937 RND_ENGINE{std::random_device{}()};

double calcTriangleArea(const Point& a, const Point& b, const Point& c)
{
    return std::abs(
        (b.x() - a.x()) * (c.y() - a.y()) -
        (b.y() - a.y()) * (c.x() - a.x())
    ) * 0.5;
}

}

namespace planar
{

Triangle::Triangle(Point a, Point b, Point c)
    : m_a(a)
    , m_b(b)
    , m_c(c)
    , m_area(calcTriangleArea(a, b, c)) { }

double Triangle::area() const
{
    return m_area;
}

Point Triangle::getRandomPoint() const
{
    std::uniform_real_distribution dist(0.0, 1.0);

    double u = dist(RND_ENGINE);
    double v = dist(RND_ENGINE);

    // Fix bias
    if (u + v > 1.0)
    {
        u = 1.0 - u;
        v = 1.0 - v;
    }

    return Point{
        m_a.x() + u * (m_b.x() - m_a.x()) + v * (m_c.x() - m_a.x()),
        m_a.y() + u * (m_b.y() - m_a.y()) + v * (m_c.y() - m_a.y())
    };
}

}