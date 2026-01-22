#pragma once
#include "defs.h"
#include "geo/point.h"

namespace game::engine
{

struct RoundResult
{
    geo::Point correctLocation;
    TPlayer2Points roundPoints;
};

struct GameState
{
    TPlayer2Points gamePoints;
    std::vector<RoundResult> finishedRounds;
    bool gameOver = false;
};


}
