#include "distance_map.h"
#include "html_reader.h"
#include "geo/point.h"

namespace
{
const QString HTML_PATH = "html/distance_map.html";
}

namespace ui::google
{

DistanceMap::DistanceMap(QWidget* parent)
    : QWebEngineView(parent)
{
    initBridge();
    resetHtmlContent({0, 0, geo::UnitType::Degrees});
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

void DistanceMap::setCenter(const geo::Point& center)
{
    resetHtmlContent(center);
}

void DistanceMap::initBridge()
{
    m_channel.registerObject("bridge", &m_bridge);
    page()->setWebChannel(&m_channel);
}

void DistanceMap::resetHtmlContent(const geo::Point& mapCenter)
{
    QString html = google::ReadAndFillApiToken(HTML_PATH);
    html.replace("__CENTER__", mapCenter.toHtmlStr());
    setHtml(html);
}

}
