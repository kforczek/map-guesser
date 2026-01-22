#pragma once

namespace game::engine
{

struct GameState;

class IRoundSystem
{
public:
    virtual ~IRoundSystem() = default;

    virtual void onRoundEnd(GameState& state) = 0;
    virtual bool isGameOver(const GameState& state) const = 0;
};

// ###############################################################################################

// Counts rounds until a certain number is reached
class FixedRoundSystem final : public IRoundSystem
{
public:
    explicit FixedRoundSystem(unsigned int roundsCnt);

    void onRoundEnd(GameState& state) override;
    bool isGameOver(const GameState& state) const override;

private:
    unsigned int m_roundsCnt = 0;
};

// ###############################################################################################

// TODO: DeathmatchRoundSystem - onRoundEnd()


}