#pragma once
#include <QWebChannel>
#include <QWebEngineView>

#include "coords_receiver.h"

namespace geo
{
class Location;
}

namespace sv
{

class InteractiveMap : public QWebEngineView
{
    Q_OBJECT
public:
    InteractiveMap(QWidget* parent, const geo::Location& startLocation);

    const std::optional<geo::Location>& currLocation() const;

signals:
    void guessMarkerPlaced();

private:
    QWebChannel m_channel;
    CoordsReceiver m_coordsBridge;

    void initCoordsListener();
    void initHtmlContent(const geo::Location& startLocation);
};

}
