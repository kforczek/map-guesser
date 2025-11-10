#pragma once
#include <QWebEngineView>

class QWidget;

namespace geo
{
class Location;
}

namespace sv
{

class StreetView : public QWebEngineView
{
public:
    StreetView(QWidget* parent = nullptr);

    void setLocation(const geo::Location& location);

private:
    QString m_htmlTemplate;

    void initViewSettings() const;
};

}
