#include "game/params.h"
#include "game/round_results.h"
#include "geo/point.h"

namespace
{

unsigned int calcRoundPoints(double distance, double totalArea, unsigned int maxPoints)
{
    if (maxPoints == 0 || totalArea <= 0.0)
        return 0;

    const double distanceForMaxPoints  = totalArea / 300000.0;
    const double distanceForZeroPoints = std::sqrt(totalArea);

    if (distance >= distanceForZeroPoints)
        return 0;

    if (distance <= distanceForMaxPoints)
        return maxPoints;

    // Normalize distance to [0, 1]
    const double t =
        (distanceForZeroPoints - distance) /
        (distanceForZeroPoints - distanceForMaxPoints);

    // Exponential curve
    constexpr double k = 4.0; // tuning parameter
    const double factor =
        (std::exp(k * t) - 1.0) /
        (std::exp(k) - 1.0);

    return static_cast<unsigned int>(
        std::round(factor * maxPoints)
    );
}

}

namespace game
{

RoundResults::RoundResults(const geo::Point& actualLoc, const geo::Point& guessedLoc, const Params& gameParams)
    : m_distanceMeters(actualLoc.distanceTo(guessedLoc))
    , m_points(calcRoundPoints(m_distanceMeters, gameParams.projectedMap.totalArea(), gameParams.maxRoundPoints))
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
