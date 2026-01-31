#pragma once

namespace game
{
struct RoundResults;
}

namespace game::mode
{

struct IGameStateObserver
{
    virtual ~IGameStateObserver() = default;

    virtual void onRoundFinished(const RoundResults& roundResults) const = 0;
    // virtual void onOpponentGuessed(TPlayerId opponentId) const = 0; // TODO: probably remove - it's more of a ServerSession responsibility
};

}