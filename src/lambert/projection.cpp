#include "lambert/projection.h"
#include "geo/consts.h"
#include "geo/map.h"
#include "planar/map.h"
#include "planar/triangulation.h"

namespace lambert
{

planar::Map project(const geo::Map& map)
{
    std::vector<planar::Region> regions;

    for (const geo::Region& region : map.regions())
        regions.push_back(project(region));

    std::vector<planar::Triangle> triangles = planar::Triangulate(regions);
    return planar::Map{std::move(triangles)};
}

planar::Region project(const geo::Region& region)
{
    std::vector<planar::Point> points;

    for (const geo::Point& point : region.points())
        points.push_back(project(point));

    return planar::Region{std::move(points)};
}

planar::Point project(const geo::Point& point)
{
    const geo::Point radPt = point.toUnit(geo::UnitType::Radians);

    const double x = geo::EARTH_R * radPt.longitude();
    const double y = geo::EARTH_R * std::sin(radPt.latitude());
    return planar::Point{x, y};
}

geo::Point unproject(const planar::Point& point)
{
    const double lat = std::asin(point.y() / geo::EARTH_R);
    const double lon = point.x() / geo::EARTH_R;

    return geo::Point{lat, lon, geo::UnitType::Radians};
}

}