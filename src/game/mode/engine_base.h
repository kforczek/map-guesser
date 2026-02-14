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
    void setObserver(IGameStateObserver& observer) override;

protected /*methods*/:
    void notifyRoundFinished();
    //void notifyOpponentGuessed(TPlayerId opponentId) const;

private:
    IGameStateObserver* m_observer = nullptr;
};

// #################################################################

}