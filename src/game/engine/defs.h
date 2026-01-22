#pragma once
#include <vector>
#include "geo/point.h"

namespace game::engine
{

using TPlayerId = size_t;
using TPlayer2Points = std::vector<double>;
using TPlayer2Guess = std::vector<std::optional<geo::Point>>;

}
