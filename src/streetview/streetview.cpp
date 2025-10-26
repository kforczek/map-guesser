#include "streetview.h"
#include "token.h"
#include "../common/location.h"

#include <QFile>
#include <QWebEngineSettings>

namespace
{

QString loadHtmlTemplate()
{
    static const QString htmlPath = "res/streetview.html";

    QFile file(htmlPath);
    file.open(QIODevice::ReadOnly);

    QString htmlTemplate = file.readAll();
    htmlTemplate.replace("__API_KEY__", sv::LoadApiToken());

    return htmlTemplate;
}

}

namespace sv
{

StreetView::StreetView(QWidget* parent /*= nullptr*/)
    : m_view(parent)
    , m_htmlTemplate(loadHtmlTemplate())
{
    initViewSettings();
    m_view.resize(1024, 768);
}

void StreetView::setLocation(const Location& location)
{
    QString fullHtml = m_htmlTemplate;
    fullHtml.replace("__LOCATION__", location.toStr());

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
