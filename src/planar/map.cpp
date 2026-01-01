#include "planar/map.h"
#include "planar/point.h"
#include <vector>
#include <algorithm>
#include <random>

namespace
{

using namespace planar;

std::mt19937 RND_ENGINE{std::random_device{}()};

double calcTotalArea(const std::vector<Triangle>& triangles)
{
    return std::accumulate(
        triangles.begin(),
        triangles.end(),
        0.0,
        [](double sum, const Triangle& triangle) {
            return sum + triangle.area();
        }
    );
}

}

namespace planar
{

Map::Map(std::vector<Triangle> triangles)
    : m_triangles(std::move(triangles))
    , m_totalArea(calcTotalArea(m_triangles)) { }

Point Map::getRandomPoint() const
{
    const Triangle& triangle = getRandomTriangle();
    return triangle.getRandomPoint();
}

const Triangle& Map::getRandomTriangle() const
{
    std::uniform_real_distribution dist{0.0, m_totalArea};
    const double rndChoice = dist(RND_ENGINE);

    double accum = 0.0;
    for (const auto& triangle : m_triangles)
    {
        accum += triangle.area();
        if (rndChoice <= accum)
            return triangle;
    }

    return m_triangles.back();
}


}
