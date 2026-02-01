#include "game/session.h"

#include "mode/engine_fixed_rounds.h"

namespace game
{

Session::Session(std::shared_ptr<Params> gameParams, game::mode::IGameStateObserver& observer)
    : m_gameParams(std::move(gameParams))
    , m_engine(std::make_unique<game::mode::FixedRoundsEngine>(m_gameParams))
{
    m_engine->setObserver(observer);
}

const Params& Session::params() const
{
    return *m_gameParams;
}

const game::mode::IEngine& Session::engine() const
{
    return *m_engine;
}

game::mode::IEngine& Session::engine()
{
    return *m_engine;
}

}
