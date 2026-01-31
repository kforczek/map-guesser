#pragma once
#include <vector>

#include "game/defs.h"
#include "geo/point.h"

namespace game::mode
{
struct IGameStateObserver;

class IEngine
{
public:
    virtual ~IEngine() = default;

    virtual void setObserver(const IGameStateObserver& observer) = 0;

    virtual double getTotalPoints(const TPlayerName& player) const = 0;
    virtual bool isGameOver() const = 0;

    virtual void registerGuess(const TPlayerName& player, const geo::Point& guess) = 0;

    virtual void startNextRound(const geo::Point& correctLocation) = 0;
    virtual void pauseGame() = 0;
};

// #################################################################

}
