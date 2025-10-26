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

    void setLocation(const Location& location);
    void show();

private:
    QWebEngineView m_view;
    QString m_htmlTemplate;

    void initViewSettings() const;
};

}
