#include "engine_base.h"

namespace game
{

EngineBase::EngineBase(IEngineStateObserver& observer)
    : m_observer(observer) { }

void EngineBase::notifyRoundFinished() const
{
    m_observer.onRoundFinished();
}

// void EngineBase::notifyOpponentGuessed(TPlayerId opponentId) const
// {
//     m_observer.onOpponentGuessed(opponentId);
// }

}
