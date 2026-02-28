#include "streetview_bridge.h"
#include "geo/point.h"

namespace ui::google
{

StreetViewBridge::StreetViewBridge(QObject* parent)
    : QObject(parent) { }

void StreetViewBridge::setLocation(const geo::Point& location)
{
    assert(location.unit() == geo::UnitType::Degrees);
    m_location = location;

    if (m_htmlReady)
        emit locationChangeRequest(m_location.latitude(), m_location.longitude());
}

void StreetViewBridge::onHtmlReady()
{
    m_htmlReady = true;

    if (m_location != geo::Point{})
        emit locationChangeRequest(m_location.latitude(), m_location.longitude());
}


}
