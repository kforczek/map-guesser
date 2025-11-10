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
public:
    InteractiveMap(QWidget* parent, const geo::Location& startLocation);

private:
    QWebChannel m_channel;
    CoordsReceiver m_coordsBridge;

    void initCoordsListener();
    void initHtmlContent(const geo::Location& startLocation);
};

}
