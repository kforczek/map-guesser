#include "game/params.h"
#include "game/round_results.h"
#include "geo/point.h"

namespace
{

unsigned int calcRoundPoints(
    double distance,        // meters
    double totalArea,       // m²
    unsigned int maxPoints)
{
    if (maxPoints == 0 || totalArea <= 0.0)
        return 0;

    // Characteristic map size (meters)
    const double mapScale = std::sqrt(totalArea / M_PI);

    // Relative distance (scale-invariant)
    const double x = distance / mapScale;

    // Tunable parameters
    constexpr double precisionRadius = 0.00001; // ~10 m on Poland-sized map
    constexpr double k = 4.0;                    // steepness

    if (x <= precisionRadius)
        return maxPoints;

    // Exponential falloff in relative space
    const double factor =
        std::exp(-k * (x - precisionRadius));

    return static_cast<unsigned int>(
        std::round(std::clamp(factor, 0.0, 1.0) * maxPoints)
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
