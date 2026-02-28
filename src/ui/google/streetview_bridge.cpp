#include "streetview_bridge.h"
#include "geo/point.h"

namespace ui::google
{

StreetViewBridge::StreetViewBridge(QObject* parent)
    : QObject(parent) { }

void StreetViewBridge::setLocation(const geo::Point& location)
{
    assert(location.unit() == geo::UnitType::Degrees);
    emit locationChangeRequest(location.latitude(), location.longitude());
}

}
