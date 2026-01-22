#pragma once
#include "params.h"
#include "engine/active_round.h"
#include "engine/round_system.h"
#include "engine/scoring_system.h"
#include "engine/state.h"

namespace game
{

// TODO: [multiplayer] this becomes ServerSession
class Session
{
public:
    explicit Session(Params gameParams);

    const Params& params() const;

private:
    Params m_gameParams;

    engine::GameState m_gameState;
    engine::ActiveRound m_activeRound;

    std::unique_ptr<engine::IScoringSystem> m_scoringSystem;
    std::unique_ptr<engine::IRoundSystem> m_roundSystem;
};

}
