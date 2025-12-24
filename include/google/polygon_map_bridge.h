#pragma once
#include <iostream>
#include <QObject>
#include <optional>
#include "geo/map.h"
#include "util/consumable.h"

namespace google
{

class PolygonMapBridge final : public QObject
{
    Q_OBJECT

public:
    using QObject::QObject;

signals:
    void mapChanged(util::Consumable<geo::Map> updatedMap);

public slots:
    void onMapChanged(const QString& regionsJson);
};

}
