#pragma once
#include <QJsonDocument>
#include "region.h"

namespace geo
{

class Map
{
public:
    static Map fromJson(const QJsonDocument& json);
    QJsonDocument toJson() const;

    const std::vector<Region>& regions() const;

    Point center() const;

private:
    std::vector<Region> m_regions;

    explicit Map(std::vector<Region> regions);
};

}
