#pragma once
#include <QWebChannel>
#include <QWebEngineView>

#include "interactive_map_bridge.h"

namespace geo
{
class Location;
}

namespace google
{

class InteractiveMap final : public QWebEngineView
{
    Q_OBJECT
public:
    InteractiveMap(QWidget* parent, const geo::Location& startLocation);

    const std::optional<geo::Location>& currLocation() const;
    void removeLocationMarker();

signals:
    void guessMarkerPlaced();

private:
    QWebChannel m_channel;
    InteractiveMapBridge m_bridge;

    void initBridge();
    void initHtmlContent(const geo::Location& startLocation);
};

}
