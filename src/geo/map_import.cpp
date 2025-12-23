#include "geo/map.h"
#include <QJsonArray>
#include <QJsonObject>

namespace
{

using namespace geo;

Point parsePoint(const QJsonObject& jsonPoint)
{
    const double latitude = jsonPoint.value("lat").toDouble();
    const double longitude = jsonPoint.value("lng").toDouble();

    return Point{latitude, longitude};
}

Region parseRegion(const QJsonArray& jsonPoints)
{
    std::vector<Point> geoPoints;
    geoPoints.reserve(jsonPoints.size());

    for (const auto& jsonPoint : jsonPoints)
    {
        if (!jsonPoint.isObject())
            throw std::invalid_argument{"Expected a point object"};

        Point point = parsePoint(jsonPoint.toObject());
        geoPoints.push_back(point);
    }

    return Region{std::move(geoPoints)};
}

std::vector<Region> parseRegions(const QJsonArray& jsonRegions)
{
    std::vector<Region> geoRegions;
    geoRegions.reserve(jsonRegions.size());

    for (const auto& jsonRegion : jsonRegions)
    {
        if (!jsonRegion.isArray())
            throw std::invalid_argument{"Expected array of points"};

        Region geoRegion = parseRegion(jsonRegion.toArray());
        geoRegions.push_back(std::move(geoRegion));
    }

    return geoRegions;
}

}

namespace geo
{

/*static*/ Map Map::fromJson(const QJsonDocument& json)
{
    if (!json.isArray())
        throw std::invalid_argument{"Expected array of regions"};

    std::vector<Region> regions = parseRegions(json.array());

    return Map{std::move(regions)};
}

}