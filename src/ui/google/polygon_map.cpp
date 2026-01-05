#include "polygon_map.h"
#include "html_reader.h"
#include "geo/point.h"

#include <QWebChannel>

namespace
{

const QString HTML_PATH = "html/polygon_map.html";

// TODO: setting actual center upon load
const geo::Point START_LOCATION{ 51.7592, 19.4550, geo::UnitType::Degrees };

}

namespace ui::google
{

PolygonMap::PolygonMap(QWidget* parent)
    : QWebEngineView(parent)
    , m_bridge(this, page())
{
    initBridge();
    resetHtmlContent(START_LOCATION);

    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
}

void PolygonMap::loadMap(const geo::Map& map)
{
    m_bridge.loadMap(map.toJson().toJson());
}

void PolygonMap::initBridge()
{
    m_channel.registerObject("bridge", &m_bridge);
    page()->setWebChannel(&m_channel);

    connect(&m_bridge, &PolygonMapBridge::mapChanged, this, &PolygonMap::mapChanged);
}

void PolygonMap::resetHtmlContent(const geo::Point& startLocation)
{
    QString html = google::ReadAndFillApiToken(HTML_PATH);
    html.replace("__CENTER__", startLocation.toHtmlStr());
    setHtml(html);
}

}
