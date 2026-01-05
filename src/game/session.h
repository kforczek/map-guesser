#pragma once
#include "params.h"

namespace game
{

class Session
{
public:
    explicit Session(Params gameParams);

    const Params& params() const;

private:
    Params m_gameParams;
};

}
