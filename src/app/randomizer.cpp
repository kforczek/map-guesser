#include "app/randomizer.h"

#include <random>
#include "geo/point.h"
#include "google/coverage.h"

namespace
{

constexpr int MAX_COVERAGE_LOOKUPS = 1000;

std::mt19937 MT_GEN{std::random_device{}()};

/*
 *GPT helps
GeoPoint generate_equal_area() {
    double sin_lat_min = std::sin(lat_min * M_PI / 180.0);
    double sin_lat_max = std::sin(lat_max * M_PI / 180.0);
    double sin_lat = lat_dist(gen) * (sin_lat_max - sin_lat_min) + sin_lat_min;
    double lat = std::asin(sin_lat) * 180.0 / M_PI;
    double lon = lon_dist(gen);
    return { lat, lon };
}

 **/

}

namespace app
{

geo::Point GetRandomStreetViewPoint()
{
    std::uniform_real_distribution latDist{49.0273953314, 54.8515359564};
    std::uniform_real_distribution lonDist{14.0745211117, 24.0299857927};

    for (int i = 0; i < MAX_COVERAGE_LOOKUPS; ++i)
    {
        double latitude = latDist(MT_GEN);
        double longitude = lonDist(MT_GEN);

        if (auto maybeCoverage = google::GetClosestCoverage({latitude, longitude}))
            return *maybeCoverage;
    }

    throw std::runtime_error("Failed to find any StreetView coverage point");
}

}