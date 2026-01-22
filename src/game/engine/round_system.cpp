#include "round_system.h"
#include "state.h"

namespace game::engine
{

FixedRoundSystem::FixedRoundSystem(unsigned int roundsCnt)
    : m_roundsCnt(roundsCnt) { }

void FixedRoundSystem::onRoundEnd(GameState& state)
{
    assert(!state.rounds.empty());
    assert(state.rounds.back().isFinished());

    // TODO start new round
}

bool FixedRoundSystem::isGameOver(const GameState& state) const
{
    return state.rounds.size() >= m_roundsCnt && state.rounds.back().isFinished();
}

}
