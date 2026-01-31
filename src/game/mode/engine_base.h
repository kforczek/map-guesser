#pragma once
#include "engine.h"
#include "game/defs.h"

namespace game
{
struct RoundResults;
}

namespace game::mode
{

struct IGameStateObserver;

// #################################################################

// TODO: or ServerEngineBase if incompatible with client
class EngineBase : public IEngine
{
public:
    void setObserver(const IGameStateObserver& observer) override;

protected /*methods*/:
    void notifyRoundFinished(const RoundResults& roundResults) const;
    //void notifyOpponentGuessed(TPlayerId opponentId) const;

private:
    const IGameStateObserver* m_observer = nullptr;
};

// #################################################################

}