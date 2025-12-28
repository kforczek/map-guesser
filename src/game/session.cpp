#include "game/session.h"

namespace game
{

Session::Session(Params gameParams)
    : m_gameParams(std::move(gameParams)) { }

const Params& Session::params() const
{
    return m_gameParams;
}

}
