#include "access.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace
{

// ####################################################################################################

const QString JSON_KEYWORD_LATITUDE = "lat";
const QString JSON_KEYWORD_LONGITUDE = "lng";

// ####################################################################################################

QJsonDocument openAsJson(const QString& filePath)
{
    QFile file{filePath};

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw ui::mapfile::AccessError{file.errorString().toStdString()};

    const QByteArray data = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);

    if (parseError.error != QJsonParseError::NoError)
        throw ui::mapfile::AccessError{parseError.errorString().toStdString()};

    return doc;
}

// ####################################################################################################
// MAP LOADING

geo::Point parsePoint(const QJsonObject& jsonPoint)
{
    const double latitude = jsonPoint.value(JSON_KEYWORD_LATITUDE).toDouble();
    const double longitude = jsonPoint.value(JSON_KEYWORD_LONGITUDE).toDouble();

    return geo::Point{latitude, longitude,  geo::UnitType::Degrees};
}

geo::Region parseRegion(const QJsonArray& jsonPoints)
{
    std::vector<geo::Point> geoPoints;
    geoPoints.reserve(jsonPoints.size());

    for (const auto& jsonPoint : jsonPoints)
    {
        if (!jsonPoint.isObject())
            throw std::invalid_argument{"Expected a point object"};

        geo::Point point = parsePoint(jsonPoint.toObject());
        geoPoints.push_back(point);
    }

    return geo::Region{std::move(geoPoints)};
}

std::vector<geo::Region> parseRegions(const QJsonArray& jsonRegions)
{
    std::vector<geo::Region> geoRegions;
    geoRegions.reserve(jsonRegions.size());

    for (const auto& jsonRegion : jsonRegions)
    {
        if (!jsonRegion.isArray())
            throw std::invalid_argument{"Expected array of points"};

        geo::Region geoRegion = parseRegion(jsonRegion.toArray());
        geoRegions.push_back(std::move(geoRegion));
    }

    return geoRegions;
}

// ####################################################################################################
// MAP SAVING

QJsonObject toJsonPoint(const geo::Point& geoPoint)
{
    QJsonObject jsonPoint;
    jsonPoint.insert(JSON_KEYWORD_LATITUDE, geoPoint.latitude());
    jsonPoint.insert(JSON_KEYWORD_LONGITUDE, geoPoint.longitude());

    return jsonPoint;
}

QJsonArray toJsonRegion(const geo::Region& geoRegion)
{
    QJsonArray jsonRegion;

    for (const geo::Point& geoPoint : geoRegion.points())
    {
        QJsonObject jsonPoint = toJsonPoint(geoPoint);
        jsonRegion.append(std::move(jsonPoint));
    }

    return jsonRegion;
}

// ####################################################################################################

}

namespace ui::mapfile
{

geo::Map LoadFromFile(const QString& path)
{
    const QJsonDocument jsonDoc = openAsJson(path);
    return FromJson(jsonDoc);
}

geo::Map FromJson(const QJsonDocument& jsonDoc)
{
    if (!jsonDoc.isArray())
        throw std::invalid_argument{"Expected array of regions"};

    std::vector<geo::Region> regions = parseRegions(jsonDoc.array());

    return geo::Map{std::move(regions)};
}

void SaveToFile(const geo::Map& map, const QString& path)
{
    const QJsonDocument jsonDoc = ToJson(map);

    QFile file{path};
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        throw AccessError{file.errorString().toStdString()};

    file.write(jsonDoc.toJson());
    file.close();
}

QJsonDocument ToJson(const geo::Map& map)
{
    QJsonArray jsonRegions;

    for (const geo::Region& geoRegion : map.regions())
    {
        QJsonArray jsonRegion = toJsonRegion(geoRegion);
        jsonRegions.append(std::move(jsonRegion));
    }

    return QJsonDocument{jsonRegions};
}

}