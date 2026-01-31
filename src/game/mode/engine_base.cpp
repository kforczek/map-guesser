#include "engine_base.h"
#include "game/round_results.h"

#include "observer.h"

namespace game::mode
{

void EngineBase::setObserver(const IGameStateObserver& observer)
{
    m_observer = &observer;
}

void EngineBase::notifyRoundFinished(const RoundResults& roundResults) const
{
    if (m_observer)
        m_observer->onRoundFinished(roundResults);
}

// void EngineBase::notifyOpponentGuessed(TPlayerId opponentId) const
// {
//     m_observer->onOpponentGuessed(opponentId);
// }

}
