#pragma once
#include "params.h"
#include "mode/engine.h"

namespace game::mode
{
struct IGameStateObserver;
}

namespace game
{

// TODO: [multiplayer] this becomes ServerSession, ClientSession should probably have no engine
class Session
{
public:
    explicit Session(std::shared_ptr<Params> gameParams, game::mode::IGameStateObserver& observer);

    const Params& params() const;

    // TODO remove direct access
    const game::mode::IEngine& engine() const;
    game::mode::IEngine& engine();

private:
    std::shared_ptr<Params> m_gameParams;
    std::unique_ptr<game::mode::IEngine> m_engine;
};

}
