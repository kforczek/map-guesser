#pragma once
#include <memory>
#include "params.h"
#include "mode/engine.h"
#include "planar/map.h"

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
    explicit Session(Params&& gameParams, game::mode::IGameStateObserver& observer);

    const Params& params() const;

    // TODO remove direct access
    const game::mode::IEngine& engine() const;
    game::mode::IEngine& engine();

private:
    std::unique_ptr<game::mode::IEngine> m_engine;
    planar::Map m_projectedMap;
};

}
