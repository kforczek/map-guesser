#include "planar/triangulation.h"
#include "planar/region.h"

namespace
{

using namespace planar;

double cross(const Point& a, const Point& b, const Point& c)
{
    return (b.x() - a.x()) * (c.y() - a.y()) -
           (b.y() - a.y()) * (c.x() - a.x());
}

bool isCCW(const std::vector<Point>& pts)
{
    double area = 0.0;
    for (size_t i = 0; i < pts.size(); ++i)
    {
        const Point& p1 = pts[i];
        const Point& p2 = pts[(i + 1) % pts.size()];
        area += (p2.x() - p1.x()) * (p2.y() + p1.y());
    }
    return area < 0;
}

bool isConvex(const Point& prev,
              const Point& curr,
              const Point& next,
              bool ccw)
{
    double z = cross(prev, curr, next);
    return ccw ? (z > 0) : (z < 0);
}

bool pointInTriangle(const Point& p,
                      const Point& a,
                      const Point& b,
                      const Point& c)
{
    double c1 = cross(p, a, b);
    double c2 = cross(p, b, c);
    double c3 = cross(p, c, a);

    bool hasNeg = (c1 < 0) || (c2 < 0) || (c3 < 0);
    bool hasPos = (c1 > 0) || (c2 > 0) || (c3 > 0);

    return !(hasNeg && hasPos);
}

}

namespace planar
{

std::vector<Triangle> Triangulate(const std::vector<Region>& regions)
{
    std::vector<Triangle> triangles;

    for (const Region& region : regions)
    {
        std::vector<Point> poly = region.points();
        if (poly.size() < 3)
            continue;

        const bool ccw = isCCW(poly);

        while (poly.size() > 3)
        {
            bool earFound = false;

            for (auto it = poly.begin(); it != poly.end(); ++it)
            {
                auto prev = (it == poly.begin())
                            ? std::prev(poly.end())
                            : std::prev(it);

                auto next = std::next(it);
                if (next == poly.end())
                    next = poly.begin();

                const Point& a = *prev;
                const Point& b = *it;
                const Point& c = *next;

                if (!isConvex(a, b, c, ccw))
                    continue;

                bool containsPoint = false;
                for (auto jt = poly.begin(); jt != poly.end(); ++jt)
                {
                    if (jt == prev || jt == it || jt == next)
                        continue;

                    if (pointInTriangle(*jt, a, b, c))
                    {
                        containsPoint = true;
                        break;
                    }
                }

                if (containsPoint)
                    continue;

                // Ear found
                triangles.emplace_back(a, b, c);
                poly.erase(it);
                earFound = true;
                break;
            }

            if (!earFound)
                break; // malformed polygon (self-intersection, etc.)
        }

        // Final triangle
        if (poly.size() == 3)
        {
            triangles.emplace_back(poly[0], poly[1], poly[2]);
        }
    }

    return triangles;
}

}