#include "geo/map.h"
#include <QJsonArray>
#include <QJsonObject>

namespace
{

using namespace geo;

QJsonObject toJsonPoint(const Point& geoPoint)
{
    QJsonObject jsonPoint;
    jsonPoint.insert("lat", geoPoint.latitude());
    jsonPoint.insert("lng", geoPoint.longitude());

    return jsonPoint;
}

QJsonArray toJsonRegion(const Region& geoRegion)
{
    QJsonArray jsonRegion;

    for (const Point& geoPoint : geoRegion.points())
    {
        QJsonObject jsonPoint = toJsonPoint(geoPoint);
        jsonRegion.append(std::move(jsonPoint));
    }

    return jsonRegion;
}

}

namespace geo
{

QJsonDocument Map::toJson() const
{
    QJsonArray jsonRegions;

    for (const Region& geoRegion : m_regions)
    {
        QJsonArray jsonRegion = toJsonRegion(geoRegion);
        jsonRegions.append(std::move(jsonRegion));
    }

    return QJsonDocument{jsonRegions};
}

}