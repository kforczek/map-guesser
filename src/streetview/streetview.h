#pragma once
#include <QWebEngineView>

class QWidget;

class Location;

namespace sv
{



class StreetView
{
public:
    explicit StreetView(QWidget* parent = nullptr);

    void show(const Location& location);

private:
    QWebEngineView m_view;
    QString m_htmlTemplate;

    void initViewSettings() const;
    void initHtmlTemplate();
};

}
