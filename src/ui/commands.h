#pragma once
#include <functional>

namespace geo
{
class Point;
}

namespace game
{
struct RoundResults;
}

namespace ui
{

// ###################################################################

enum class ErrorAction
{
    Retry,
    Abort
};

// ###################################################################

struct Commands
{
    std::function<void(const geo::Point& mapCenter)> setMapCenter;
    std::function<void(const geo::Point& location)> startNextRound;
    std::function<void(const std::string&)> showPlayerGuessed;
    std::function<void(const game::RoundResults&)> showRoundResults;

    std::function<ErrorAction(const std::string& what)> showErrorMessage;
};

// ###################################################################

}
