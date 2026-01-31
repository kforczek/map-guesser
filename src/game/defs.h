#pragma once
#include <string>
#include <unordered_map>

#include "geo/point.h"

namespace game
{

using TPlayerName = std::string;
using TPlayer2Guess = std::unordered_map<TPlayerName, geo::Point>;
using TPlayer2Points = std::unordered_map<TPlayerName, unsigned int>;

}
