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
    , m_bridge(new DistanceMapBridge(this))
{
    initBridge();
    initHtmlContent({0, 0, geo::UnitType::Degrees});
}

// ReSharper disable once CppMemberFunctionMayBeConst
void DistanceMap::setActualLocation(const geo::Point& location)
{
    m_bridge->setMarkerActual(location);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void DistanceMap::setGuessedLocation(const geo::Point& location)
{
    m_bridge->setMarkerGuessed(location);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void DistanceMap::setDistance(const double distance)
{
    m_bridge->setDistance(distance);
}

void DistanceMap::setCenter(const geo::Point& center)
{
    initHtmlContent(center);
}

void DistanceMap::initBridge()
{
    auto* channel = new QWebChannel(this);
    channel->registerObject("bridge", m_bridge);
    page()->setWebChannel(channel);
}

void DistanceMap::initHtmlContent(const geo::Point& mapCenter)
{
    QString html = google::ReadAndFillApiToken(HTML_PATH);
    html.replace("__CENTER__", mapCenter.toHtmlStr());
    setHtml(html);
}

}
