#pragma once
#include <string>
#include <unordered_map>
#include <optional>

#include "geo/point.h"

namespace game
{

using TPlayerName = std::string;
using TPlayer2Guess = std::unordered_map<TPlayerName, std::optional<geo::Point>>;
using TPlayer2Points = std::unordered_map<TPlayerName, unsigned int>;

}
