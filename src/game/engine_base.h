#pragma once
#include "engine.h"

namespace game
{
struct IEngineStateObserver;

// #################################################################

// TODO: or ServerEngineBase if incompatible with client
class EngineBase : public IEngine
{
public:
    explicit EngineBase(IEngineStateObserver& observer);

protected /*methods*/:
    void notifyRoundFinished() const;
    //void notifyOpponentGuessed(TPlayerId opponentId) const;

private:
    IEngineStateObserver& m_observer;
};

// #################################################################

}