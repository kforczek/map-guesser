#pragma once
#include <QWebEngineView>
#include "geo/map.h"
#include "util/consumable.h"

namespace ui::google
{

class PolygonMapBridge;

class PolygonMap final : public QWebEngineView
{
    Q_OBJECT
public:
    explicit PolygonMap(QWidget* parent);

    void loadMap(const geo::Map& map);

signals:
    void mapChanged(util::Consumable<geo::Map> updatedMap);

private:
    PolygonMapBridge* m_bridge = nullptr;

    void initBridge();
    void initHtmlContent();
};

}
