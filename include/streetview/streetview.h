#pragma once
#include <QWebEngineView>
#include "geo/location.h"

class QWidget;

namespace sv
{

class StreetView : public QWebEngineView
{
public:
    StreetView(QWidget* parent = nullptr);

    const geo::Location& getLocation() const;
    void setLocation(const geo::Location& location);
    void returnToStart();

private:
    QString m_htmlTemplate;
    geo::Location m_location;

    void initViewSettings() const;
};

}
