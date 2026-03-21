#include "polygon_map_bridge.h"

#include <QJsonDocument>
#include <QWidget>
#include <QWebEnginePage>

#include "ui/mapfile/access.h"

namespace ui::google
{

PolygonMapBridge::PolygonMapBridge(QWidget* parent, QWebEnginePage* page)
    : QObject(parent)
    , m_page(page)
{
    if (!m_page)
        throw std::invalid_argument("page must not be null");
}

void PolygonMapBridge::loadMap(const QString& jsonMap)
{
    m_suppressSignals = true;

    const QString js = QStringLiteral("loadMapFromJson(%1);").arg(jsonMap);
    m_page->runJavaScript(js);

    m_suppressSignals = false;
}

void PolygonMapBridge::onMapChanged(const QString& jsonMap)
{
    if (m_suppressSignals)
        return;

    const auto jsonDoc = QJsonDocument::fromJson(jsonMap.toUtf8());

    auto geoMap = mapfile::FromJson(jsonDoc);
    auto consumableGeoMap = util::make_consumable<geo::Map>(std::move(geoMap));

    emit mapChanged(std::move(consumableGeoMap));
}

}
