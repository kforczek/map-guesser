#include "google/polygon_map_bridge.h"

namespace google
{

void PolygonMapBridge::onRegionsChanged(const QString& regionsJson)
{
    //TODO
    emit regionChanged();
}

}
