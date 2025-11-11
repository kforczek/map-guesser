#include "game/results.h"
#include "geo/location.h"

namespace game
{

RoundResults::RoundResults(
    const db::LocationPool& locPool,
    const geo::Location& actualLoc,
    const geo::Location& guessedLoc)
        : m_distanceMeters(actualLoc.distanceTo(guessedLoc))
{
}

double RoundResults::distanceMeters() const
{
    return m_distanceMeters;
}

unsigned int RoundResults::points() const
{
    return m_points;
}

}
