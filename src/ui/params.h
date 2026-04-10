#pragma once
#include <qdatetime.h>
#include <QStringList>

#include "geo/map.h"

namespace ui
{

struct Params
{
    geo::Map map;

    QStringList playerNames;

    int roundsCnt = 0;
    int maxRoundPoints = 0;

    std::optional<QTime> roundTimeLimit;
};

}
