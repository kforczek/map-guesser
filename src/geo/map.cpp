#include "geo/map.h"
#include <ranges>

namespace geo
{

Map::Map(std::vector<Region> regions)
    : m_regions(std::move(regions))
{
    if (m_regions.empty())
        throw std::invalid_argument{"Map must contain at least one region"};
}

Point Map::center() const
{
    const auto allPoints =
        m_regions
        | std::views::transform(&Region::points)
        | std::views::join;

    const auto [minLatIt, maxLatIt] = std::ranges::minmax(allPoints, std::less{}, &Point::latitude);
    const auto [minLngIt, maxLngIt] = std::ranges::minmax(allPoints, std::less{}, &Point::longitude);

    const double latCenter = (minLatIt.latitude() + maxLatIt.latitude()) / 2;
    const double lngCenter = (minLngIt.longitude() + maxLngIt.longitude()) / 2;

    return Point{latCenter, lngCenter};
}

}