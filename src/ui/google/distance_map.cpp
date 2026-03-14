#include "distance_map.h"

#include <QMessageBox>

#include "html_reader.h"
#include "geo/point.h"
#include "ui/api_usage/counter.h"

namespace
{
const QString HTML_PATH = "html/distance_map.html";
}

namespace ui::google
{

DistanceMap::DistanceMap(QWidget* parent, api_usage::Counter& counter)
    : QWebEngineView(parent)
    , m_bridge(new DistanceMapBridge(this))
{
    if (!tryIncreaseApiCounter(counter))
        return;

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

bool DistanceMap::tryIncreaseApiCounter(api_usage::Counter& counter)
{
    if (counter.isLimitReached(user::ApiCategory::Maps))
    {
        QMessageBox::critical(this, "Maps", "You have reached the limit of Maps API usage.");
        return false;
    }

    counter.logApiUsage(user::ApiCategory::Maps);
    return true;
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
