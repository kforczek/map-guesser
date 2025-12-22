#include "google/distance_map.h"

#include "db/location_pool.h"
#include "google/html_reader.h"

namespace
{
const QString HTML_PATH = "html/distance_map.html";
}

namespace google
{

DistanceMap::DistanceMap(QWidget* parent, const geo::Point& mapCenter)
    : QWebEngineView(parent)
{
    initBridge();
    initHtmlContent(mapCenter);
}

void DistanceMap::setActualLocation(const geo::Point& location)
{
    m_bridge.setMarkerActual(location);
}

void DistanceMap::setGuessedLocation(const geo::Point& location)
{
    m_bridge.setMarkerGuessed(location);
}

void DistanceMap::setDistance(const double distance)
{
    m_bridge.setDistance(distance);
}

void DistanceMap::initBridge()
{
    m_channel.registerObject("bridge", &m_bridge);
    page()->setWebChannel(&m_channel);
}

void DistanceMap::initHtmlContent(const geo::Point& mapCenter)
{
    QString html = google::ReadAndFillApiToken(HTML_PATH);
    html.replace("__CENTER__", mapCenter.toHtmlStr());
    setHtml(html);
}

}
