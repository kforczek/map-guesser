#include "interactive_map.h"
#include "html_reader.h"
#include "geo/point.h"

#include <QWebChannel>

namespace
{
const QString HTML_PATH = "html/interactive_map.html";
}

namespace ui::google
{

InteractiveMap::InteractiveMap(QWidget* parent)
    : QWebEngineView(parent)
    , m_bridge(this)
{
    initBridge();
    resetHtmlContent({0, 0, geo::UnitType::Degrees});
}

const std::optional<geo::Point>& InteractiveMap::currLocation() const
{
    return m_bridge.location();
}

void InteractiveMap::removeLocationMarker()
{
    m_bridge.removeLocationMarker();
}

void InteractiveMap::setCenter(const geo::Point& center)
{
    resetHtmlContent(center);
}

void InteractiveMap::initBridge()
{
    m_channel.registerObject("bridge", &m_bridge);
    page()->setWebChannel(&m_channel);

    connect(&m_bridge, &InteractiveMapBridge::locationSet, this, [this](){ emit guessMarkerPlaced(); });
}

void InteractiveMap::resetHtmlContent(const geo::Point& startLocation)
{
    QString html = google::ReadAndFillApiToken(HTML_PATH);
    html.replace("__CENTER__", startLocation.toHtmlStr());
    setHtml(html);
}

}
