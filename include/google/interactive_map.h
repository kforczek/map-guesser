#pragma once
#include <QWebChannel>
#include <QWebEngineView>

#include "interactive_map_bridge.h"

namespace geo
{
class Point;
}

namespace google
{

class InteractiveMap final : public QWebEngineView
{
    Q_OBJECT
public:
    explicit InteractiveMap(QWidget* parent);

    const std::optional<geo::Point>& currLocation() const;
    void removeLocationMarker();

    void setCenter(const geo::Point& center);

signals:
    void guessMarkerPlaced();

private:
    QWebChannel m_channel;
    InteractiveMapBridge m_bridge;

    void initBridge();
    void resetHtmlContent(const geo::Point& startLocation);
};

}
