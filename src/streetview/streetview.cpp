#include "streetview.h"
#include "token.h"
#include "../common/location.h"

#include <QFile>
#include <QWebEngineSettings>

namespace
{

inline QString loadHtmlTemplate()
{
    static const QString htmlPath = "res/streetview.html";

    QFile file(htmlPath);
    file.open(QIODevice::ReadOnly);
    return file.readAll();
}

}

namespace sv
{

StreetView::StreetView(QWidget* parent /*= nullptr*/)
    : m_view(parent)
    , m_htmlTemplate(loadHtmlTemplate())
{
    initViewSettings();
    initHtmlTemplate();
    m_view.resize(1024, 768);
}

void StreetView::show(const Location& location)
{
    QString fullHtml = m_htmlTemplate;
    fullHtml.replace("__LOCATION__", location.toStr());

    m_view.setHtml(m_htmlTemplate);
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

void StreetView::initHtmlTemplate()
{
    std::unordered_map<QString, QString> replacements{
        {"__API_KEY__", sv::LoadApiToken()}
    };

    for (const auto& [key, value] : replacements)
        m_htmlTemplate.replace(key, value);
}

}
