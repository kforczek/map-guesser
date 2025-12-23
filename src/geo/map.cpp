#include "geo/map.h"

namespace geo
{

Map::Map(std::vector<Region> regions)
    : m_regions(std::move(regions))
{
    if (m_regions.empty())
        throw std::invalid_argument{"Map must contain at least one region"};
}

}