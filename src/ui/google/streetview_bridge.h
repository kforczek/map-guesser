#pragma once
#include <QObject>

namespace geo
{
class Point;
}

namespace ui::google
{

class StreetViewBridge final : public QObject
{
    Q_OBJECT
public:
    explicit StreetViewBridge(QObject* parent);

    void setLocation(const geo::Point& location);

signals:
    void locationChangeRequest(double lat, double lng);
};

}