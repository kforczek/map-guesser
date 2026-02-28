#include "streetview.h"
#include "google/token.h"
#include "html_reader.h"
#include "geo/point.h"
#include "streetview_bridge.h"

#include <QFile>
#include <QWebChannel>
#include <QWebEngineSettings>

namespace
{
const QString HTML_PATH = "html/streetview.html";
}

namespace ui::google
{

StreetView::StreetView(QWidget* parent /*= nullptr*/)
    : QWebEngineView(parent)
    , m_bridge(new StreetViewBridge(this))
{
    initViewSettings();
    initBridge();
    initHtmlContent();
}

const geo::Point& StreetView::getLocation() const
{
    return m_location;
}

void StreetView::setLocation(const geo::Point& location)
{
    m_location = location;
    m_bridge->setLocation(location);
}

void StreetView::returnToStart()
{
    setLocation(m_location);
}

void StreetView::initViewSettings() const
{
    settings()->setAttribute(QWebEngineSettings::WebGLEnabled, true);
    settings()->setAttribute(QWebEngineSettings::Accelerated2dCanvasEnabled, true);
    settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
    settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);
    settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    settings()->setAttribute(QWebEngineSettings::AllowRunningInsecureContent, false);
    settings()->setAttribute(QWebEngineSettings::ScrollAnimatorEnabled, true);
    settings()->setAttribute(QWebEngineSettings::LocalStorageEnabled, true);
}

void StreetView::initBridge()
{
    auto* channel = new QWebChannel(this);
    channel->registerObject("bridge", m_bridge);
    page()->setWebChannel(channel);
}

void StreetView::initHtmlContent()
{
    const QString html = google::ReadAndFillApiToken(HTML_PATH);
    setHtml(html);
}

}
