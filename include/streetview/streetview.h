#pragma once
#include <QWebEngineView>

class QWidget;

namespace geo
{
class Location;
}

namespace sv
{

class StreetView
{
public:
    explicit StreetView(QWidget* parent = nullptr);

    void setLocation(const geo::Location& location);
    void show();

private:
    QWebEngineView m_view;
    QString m_htmlTemplate;

    void initViewSettings() const;
};

}
