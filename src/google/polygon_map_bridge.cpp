#include "google/polygon_map_bridge.h"
#include <QWidget>
#include <QWebEnginePage>

namespace google
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
    auto geoMap = geo::Map::fromJson(jsonDoc);
    emit mapChanged(std::move(geoMap));
}

}
