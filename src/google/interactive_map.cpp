#include "google/interactive_map.h"
#include "google/html_reader.h"
#include "geo/point.h"

#include <QWebChannel>

namespace
{
const QString HTML_PATH = "html/interactive_map.html";
}

namespace google
{

InteractiveMap::InteractiveMap(QWidget* parent, const geo::Point& startLocation)
    : QWebEngineView(parent)
    , m_bridge(this)
{
    initBridge();
    initHtmlContent(startLocation);
}

const std::optional<geo::Point>& InteractiveMap::currLocation() const
{
    return m_bridge.location();
}

void InteractiveMap::removeLocationMarker()
{
    m_bridge.removeLocationMarker();
}

void InteractiveMap::initBridge()
{
    m_channel.registerObject("bridge", &m_bridge);
    page()->setWebChannel(&m_channel);

    connect(&m_bridge, &InteractiveMapBridge::locationSet, this, [this](){ emit guessMarkerPlaced(); });
}

void InteractiveMap::initHtmlContent(const geo::Point& startLocation)
{
    QString html = google::ReadAndFillApiToken(HTML_PATH);
    html.replace("__CENTER__", startLocation.toHtmlStr());
    setHtml(html);
}

}
