#pragma once
#include "region.h"
#include "triangle.h"

namespace planar
{

class Map
{
public:
    Map() = default;
    explicit Map(std::vector<Triangle> triangles);

    Point getRandomPoint() const;
    double totalArea() const;

private:
    std::vector<Triangle> m_triangles;
    double m_totalArea = 0.0;

    const Triangle& getRandomTriangle() const;
};

}
