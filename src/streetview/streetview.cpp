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
    : m_view(parent)
    , m_htmlTemplate(sv::ReadAndFillApiToken(HTML_PATH))
{
    initViewSettings();
    m_view.resize(1024, 768);
}

void StreetView::setLocation(const geo::Location& location)
{
    QString fullHtml = m_htmlTemplate;
    fullHtml.replace("__LOCATION__", location.toHtmlStr());

    m_view.setHtml(fullHtml);
}

void StreetView::show()
{
    m_view.show();
}

void StreetView::initViewSettings() const
{
    auto* settings = m_view.settings();
    if (!settings)
    {
        qDebug() << "Failed to fetch view settings";
        return;
    }

    settings->setAttribute(QWebEngineSettings::WebGLEnabled, true);
    settings->setAttribute(QWebEngineSettings::Accelerated2dCanvasEnabled, true);
    settings->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
    settings->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);
    settings->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    settings->setAttribute(QWebEngineSettings::AllowRunningInsecureContent, false);
    settings->setAttribute(QWebEngineSettings::ScrollAnimatorEnabled, true);
    settings->setAttribute(QWebEngineSettings::LocalStorageEnabled, true);
}

}
