#include "google/polygon_map_bridge.h"

namespace google
{

void PolygonMapBridge::onMapChanged(const QString& jsonMap)
{
    const auto jsonDoc = QJsonDocument::fromJson(jsonMap.toUtf8());
    auto geoMap = geo::Map::fromJson(jsonDoc);
    emit mapChanged(std::move(geoMap));
}

}
