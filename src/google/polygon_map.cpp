#include "google/polygon_map.h"
#include "google/html_reader.h"
#include "geo/location.h"

#include <QWebChannel>

namespace
{

const QString HTML_PATH = "html/polygon_map.html";

const geo::Location START_LOCATION{ 51.7592, 19.4550 };

}

namespace google
{

PolygonMap::PolygonMap(QWidget* parent)
    : QWebEngineView(parent)
    , m_bridge(this)
{
    initBridge();
    resetHtmlContent(START_LOCATION);

    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
}

void PolygonMap::initBridge()
{
    m_channel.registerObject("bridge", &m_bridge);
    page()->setWebChannel(&m_channel);

    //connect(&m_bridge, &PolygonMapBridge::regionChanged, this, [this](){ emit guessMarkerPlaced(); });
}

void PolygonMap::resetHtmlContent(const geo::Location& startLocation)
{
    QString html = google::ReadAndFillApiToken(HTML_PATH);
    html.replace("__CENTER__", startLocation.toHtmlStr());
    setHtml(html);
}

}
