#pragma once
#include <optional>
#include "geo/point.h"

namespace google
{

// ##########################################################

std::optional<geo::Point> GetClosestCoverage(const geo::Point& location);

// ##########################################################

class CoverageLookupError final : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

// ##########################################################

}