#include "polygon_map.h"

#include <QMessageBox>

#include "html_reader.h"
#include "polygon_map_bridge.h"
#include "ui/mapfile/access.h"
#include <QWebChannel>

#include "ui/api_usage/limit.h"

namespace
{

const QString HTML_PATH = "html/polygon_map.html";

}

namespace ui::google
{

PolygonMap::PolygonMap(QWidget* parent)
    : QWebEngineView(parent)
    , m_bridge(new PolygonMapBridge(this, page()))
{
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    if (!api_usage::TryLogUsage(this, user::ApiCategory::Maps))
        return;

    initBridge();
    initHtmlContent();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void PolygonMap::loadMap(const geo::Map& map)
{
    m_bridge->loadMap(mapfile::ToJson(map).toJson());
}

void PolygonMap::initBridge()
{
    auto* channel = new QWebChannel(this);
    channel->registerObject("bridge", m_bridge);
    page()->setWebChannel(channel);

    connect(m_bridge, &PolygonMapBridge::mapChanged, this, &PolygonMap::mapChanged);
}

void PolygonMap::initHtmlContent()
{
    const QString html = google::ReadAndFillApiToken(HTML_PATH);
    setHtml(html);
}

}
