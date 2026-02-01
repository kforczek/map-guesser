#pragma once
#include "engine_base.h"

namespace game
{
struct Params;
}

namespace game::mode
{

class FixedRoundsEngine final : public EngineBase
{
public:
    explicit FixedRoundsEngine(std::shared_ptr<Params> gameParams);

    double getTotalPoints(const TPlayerName& player) const override;
    bool isGameOver() const override;

    void registerGuess(const TPlayerName& player, const geo::Point& guess) override;

    void startNextRound(const geo::Point& correctLocation) override;
    void pauseGame() override;

private:
    std::shared_ptr<Params> m_gameParams;

    size_t m_roundNumber = 0;
    geo::Point m_correctLocation;
    TPlayer2Guess m_guesses;

    void finishRound();
};

}