#include "streetview/distance_map.h"

#include "db/location_pool.h"
#include "streetview/html_reader.h"

namespace
{
const QString HTML_PATH = "html/distance_map.html";
}

namespace sv
{

DistanceMap::DistanceMap(QWidget* parent, const geo::Location& mapCenter)
    : QWebEngineView(parent)
{
    initDistanceConnector();
    initHtmlContent(mapCenter);
}

void DistanceMap::setActualLocation(const geo::Location& location)
{
    m_distanceUpdater.setMarkerActual(location);
}

void DistanceMap::setGuessedLocation(const geo::Location& location)
{
    m_distanceUpdater.setMarkerGuessed(location);
}

void DistanceMap::setDistance(const double distance)
{
    m_distanceUpdater.setDistance(distance);
}

void DistanceMap::initDistanceConnector()
{
    m_channel.registerObject("distanceUpdater", &m_distanceUpdater);
    page()->setWebChannel(&m_channel);
}

void DistanceMap::initHtmlContent(const geo::Location& mapCenter)
{
    QString html = sv::ReadAndFillApiToken(HTML_PATH);
    html.replace("__CENTER__", mapCenter.toHtmlStr());
    setHtml(html);
}

}
