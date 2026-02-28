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
    initHtmlContent();
}

void DistanceMap::setCenter(const geo::Point& center)
{
    m_bridge->setCenter(center);
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

void DistanceMap::initBridge()
{
    auto* channel = new QWebChannel(this);
    channel->registerObject("bridge", m_bridge);
    page()->setWebChannel(channel);
}

void DistanceMap::initHtmlContent()
{
    const QString html = google::ReadAndFillApiToken(HTML_PATH);
    setHtml(html);
}

}
