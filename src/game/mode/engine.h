#pragma once

#include "game/defs.h"
#include "game/round_results.h"
#include "geo/point.h"

namespace game
{
struct Params;
}

namespace game::mode
{
struct IGameStateObserver;

class IEngine
{
public:
    virtual ~IEngine() = default;

    virtual void setObserver(IGameStateObserver& observer) = 0;

    virtual const Params& params() const = 0;
    virtual RoundResults calcRoundResults() const = 0;
    virtual double getTotalPoints(const TPlayerName& player) const = 0;
    virtual bool isGameOver() const = 0;

    virtual void registerGuess(const TPlayerName& player, const geo::Point& guess) = 0;

    virtual void startNextRound(const geo::Point& correctLocation) = 0;
    virtual void pauseGame() = 0;
};

// #################################################################

}
