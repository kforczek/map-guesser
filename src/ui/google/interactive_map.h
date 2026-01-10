#pragma once
#include <QWebEngineView>

#include "interactive_map_bridge.h"

namespace geo
{
class Point;
}

namespace ui::google
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
    InteractiveMapBridge* m_bridge = nullptr;

    void initBridge();
    void resetHtmlContent(const geo::Point& startLocation);
};

}
