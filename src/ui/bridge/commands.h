#pragma once
#include <functional>
#include <string>

namespace geo
{
class Point;
}

namespace game
{
struct RoundResults;
}

namespace ui::bridge
{

// ###################################################################

struct Commands
{
    enum class ErrorAction
    {
        Retry,
        Abort
    };

    using TCmdSetMapCenter = std::function<void(const geo::Point& mapCenter)>;
    using TCmdStartNextRound = std::function<void(const geo::Point& location)>;
    using TCmdShowPlayerGuessed = std::function<void(const std::string& playerName)>;
    using TCmdShowRoundResults = std::function<void(const game::RoundResults& results, bool isGameOver)>;
    using TCmdShowErrorMessage = std::function<ErrorAction(const std::string& what)>;

    TCmdSetMapCenter        setMapCenter;
    TCmdStartNextRound      startNextRound;
    TCmdShowPlayerGuessed   showPlayerGuessed;
    TCmdShowRoundResults    showRoundResults;
    TCmdShowErrorMessage    showErrorMessage;
};

// ###################################################################

}
