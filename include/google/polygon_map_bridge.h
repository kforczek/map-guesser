#pragma once
#include <iostream>
#include <QObject>
#include <optional>

namespace google
{

class PolygonMapBridge final : public QObject
{
    Q_OBJECT

public:
    using QObject::QObject;

signals:
    void regionsChanged(/* TODO vector of points */);

public slots:
    void onRegionsChanged(const QString& regionsJson);
};

}
