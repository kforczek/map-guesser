#include "app/random_point.h"

#include <random>
#include "planar/map.h"
#include "google/coverage.h"
#include "lambert/projection.h"

namespace
{
constexpr int MAX_COVERAGE_LOOKUPS = 1000;
}

namespace app
{

geo::Point GetRandomStreetViewPoint(const planar::Map& projectedMap)
{
    for (int i = 0; i < MAX_COVERAGE_LOOKUPS; ++i)
    {
        const planar::Point projectedPoint = projectedMap.getRandomPoint();
        const geo::Point geoPoint = lambert::unproject(projectedPoint);

        if (auto maybeCoverage = google::GetClosestCoverage(geoPoint))
            return *maybeCoverage;
    }

    throw std::runtime_error("Failed to find any StreetView coverage point");
}

}