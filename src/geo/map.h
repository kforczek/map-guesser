#pragma once
#include <vector>
#include "region.h"

namespace geo
{

class Map
{
public:
    Map() = default;
    explicit Map(std::vector<Region> regions);

    const std::vector<Region>& regions() const;

    Point center() const;

private:
    std::vector<Region> m_regions;
};

}
