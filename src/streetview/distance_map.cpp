#include "streetview/distance_map.h"

#include "db/location_pool.h"
#include "streetview/html_reader.h"

namespace
{
const QString HTML_PATH = "html/distance_map.html";
}

namespace sv
{

DistanceMap::DistanceMap(QWidget* parent /*= nullptr*/)
{
    initDistanceConnector();
    initHtmlContent();
}

void DistanceMap::setPointA(const geo::Location& location)
{
    m_distanceUpdater.setMarkerA(location);
}

void DistanceMap::setPointB(const geo::Location& location)
{
    m_distanceUpdater.setMarkerB(location);
}

void DistanceMap::initDistanceConnector()
{
    m_channel.registerObject("distanceUpdater", &m_distanceUpdater);
    page()->setWebChannel(&m_channel);
}

void DistanceMap::initHtmlContent()
{
    QString html = sv::ReadAndFillApiToken(HTML_PATH);

    // TODOOOOO
    html.replace("__CENTER__", db::LocationPool{}.center().toHtmlStr());
    setHtml(html);
}

}
