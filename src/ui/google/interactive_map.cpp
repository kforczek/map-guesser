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
    , m_bridge(new InteractiveMapBridge(this))
{
    initBridge();
    initHtmlContent();
}

const std::optional<geo::Point>& InteractiveMap::currLocation() const
{
    return m_bridge->location();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void InteractiveMap::removeLocationMarker()
{
    m_bridge->removeLocationMarker();
}

void InteractiveMap::setCenter(const geo::Point& center)
{
    m_bridge->setCenter(center);
}

void InteractiveMap::initBridge()
{
    auto* channel = new QWebChannel(this);
    channel->registerObject("bridge", m_bridge);
    page()->setWebChannel(channel);

    connect(m_bridge, &InteractiveMapBridge::locationSet, this, &InteractiveMap::guessMarkerPlaced);
}

void InteractiveMap::initHtmlContent()
{
    const QString html = google::ReadAndFillApiToken(HTML_PATH);
    setHtml(html);
}

}
