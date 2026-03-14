#pragma once
#include <QWebEngineView>
#include "geo/map.h"
#include "util/consumable.h"

namespace ui::api_usage
{
class Counter;
}

namespace ui::google
{

class PolygonMapBridge;

class PolygonMap final : public QWebEngineView
{
    Q_OBJECT
public:
    explicit PolygonMap(QWidget* parent, api_usage::Counter& counter);

    void loadMap(const geo::Map& map);

signals:
    void mapChanged(util::Consumable<geo::Map> updatedMap);

private:
    PolygonMapBridge* m_bridge = nullptr;

    bool tryIncreaseApiCounter(api_usage::Counter& counter);

    void initBridge();
    void initHtmlContent();
};

}
