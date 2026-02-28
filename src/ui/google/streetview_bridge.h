#pragma once
#include <QObject>
#include "geo/point.h"

namespace ui::google
{

class StreetViewBridge final : public QObject
{
    Q_OBJECT
public:
    explicit StreetViewBridge(QObject* parent);

    void setLocation(const geo::Point& location);

public slots:
    void onHtmlReady();

signals:
    void locationChangeRequest(double lat, double lng);

private:
    bool m_htmlReady = false;
    geo::Point m_location;
};

}