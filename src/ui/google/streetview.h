#pragma once
#include <QWebEngineView>
#include "geo/point.h"

class QWidget;

namespace ui::google
{

class StreetView : public QWebEngineView
{
public:
    StreetView(QWidget* parent = nullptr);

    const geo::Point& getLocation() const;
    void setLocation(const geo::Point& location);
    void returnToStart();

private:
    QString m_htmlTemplate;
    geo::Point m_location;

    void initViewSettings() const;
};

}
