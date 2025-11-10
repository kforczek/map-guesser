#include "streetview/interactive_map.h"
#include "streetview/html_reader.h"
#include "geo/location.h"

#include <QWebChannel>

namespace
{
const QString HTML_PATH = "html/interactive_map.html";
}

namespace sv
{

InteractiveMap::InteractiveMap(QWidget* parent, const geo::Location& startLocation)
    : QWebEngineView(parent)
    , m_coordsBridge(this)
{
    initCoordsListener();
    initHtmlContent(startLocation);
}

void InteractiveMap::initCoordsListener()
{
    m_channel.registerObject("coordsReceiver", &m_coordsBridge);
    page()->setWebChannel(&m_channel);
}

void InteractiveMap::initHtmlContent(const geo::Location& startLocation)
{
    QString html = sv::ReadAndFillApiToken(HTML_PATH);
    html.replace("__CENTER__", startLocation.toHtmlStr());
    setHtml(html);
}

}
