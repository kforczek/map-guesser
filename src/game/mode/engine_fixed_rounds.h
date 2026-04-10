#pragma once
#include <memory>
#include "engine_base.h"
#include "game/params.h"

namespace game::mode
{

class FixedRoundsEngine final : public EngineBase
{
public:
    explicit FixedRoundsEngine(Params&& gameParams);

    const Params& params() const override;
    RoundResults calcRoundResults() const override;
    double getTotalPoints(const TPlayerName& player) const override;
    bool isGameOver() const override;

    void registerPlayerGuess(const TPlayerName& player, const std::optional<geo::Point>& guess) override;

    void startNextRound(const geo::Point& correctLocation) override;
    void pauseGame() override;

private:
    Params m_gameParams;

    size_t m_roundNumber = 0;
    geo::Point m_correctLocation;
    TPlayer2Guess m_guesses;
};

}