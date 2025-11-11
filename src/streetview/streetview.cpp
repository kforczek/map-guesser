#include "streetview/streetview.h"
#include "streetview/token.h"
#include "streetview/html_reader.h"
#include "geo/location.h"

#include <QFile>
#include <QWebEngineSettings>

namespace
{
const QString HTML_PATH = "html/streetview.html";
}

namespace sv
{

StreetView::StreetView(QWidget* parent /*= nullptr*/)
    : QWebEngineView(parent)
    , m_htmlTemplate(sv::ReadAndFillApiToken(HTML_PATH))
{
    initViewSettings();
}

const geo::Location& StreetView::getLocation() const
{
    return m_location;
}

void StreetView::setLocation(const geo::Location& location)
{
    m_location = location;

    QString fullHtml = m_htmlTemplate;
    fullHtml.replace("__LOCATION__", location.toHtmlStr());
    setHtml(fullHtml);
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

}
