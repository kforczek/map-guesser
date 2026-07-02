#pragma once

#include "game/defs.h"
#include "game/round_results.h"
#include "geo/point.h"

namespace game
{
struct Params;

// ###################################################################################################################

class IEngine
{
public:
    virtual ~IEngine() = default;

    virtual const Params& params() const = 0;
    virtual RoundResults calcRoundResults() const = 0;
    virtual double getTotalPoints(const TPlayerName& player) const = 0;
    virtual bool isGameOver() const = 0;

    virtual void registerPlayerGuess(const TPlayerName& player, const std::optional<geo::Point>& guess) = 0;

    virtual void startNextRound(const geo::Point& correctLocation) = 0;
    virtual void pauseGame() = 0;
};

// ###################################################################################################################

struct IEngineStateObserver
{
    virtual ~IEngineStateObserver() = default;

    virtual void onRoundFinished() = 0;
    // virtual void onOpponentGuessed(TPlayerId opponentId) const = 0; // TODO: probably remove - it's more of a ServerSession responsibility
};

// ###################################################################################################################

}
