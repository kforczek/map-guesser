#include "app/results.h"
#include "geo/point.h"

namespace app
{

RoundResults::RoundResults(
    const geo::Point& actualLoc,
    const geo::Point& guessedLoc)
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
