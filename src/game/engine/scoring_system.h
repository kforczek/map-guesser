#pragma once
#include "defs.h"

namespace game::engine
{

struct GameState;

// ###############################################################################################

class IScoringSystem
{
public:
    virtual ~IScoringSystem() = default;

    virtual void applyRoundResults(GameState& state, const TPlayer2Points& playerPoints) = 0;
};

// ###############################################################################################

// Each player's points get appended to their total score
class AdditiveScoringSystem final : public IScoringSystem
{
public:
    void applyRoundResults(GameState& state, const TPlayer2Points& roundPoints) override;
};

// ###############################################################################################

// TODO: DeathmatchScoringSystem (everybody loses diff to best guess)

}
