#pragma once
#include <iostream>
#include <QObject>
#include <optional>
#include "geo/map.h"
#include "util/consumable.h"

class QWidget;
class QWebEnginePage;

namespace ui::google
{

class PolygonMapBridge final : public QObject
{
    Q_OBJECT

public:
    PolygonMapBridge(QWidget* parent, QWebEnginePage* page);

    Q_INVOKABLE void loadMap(const QString& jsonMap);

signals:
    void mapChanged(util::Consumable<geo::Map> updatedMap);

public slots:
    void onMapChanged(const QString& jsonMap);

private:
    QWebEnginePage* m_page = nullptr;
    bool m_suppressSignals = false;
};

}
