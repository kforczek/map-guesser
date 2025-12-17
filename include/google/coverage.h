#pragma once
#include <optional>
#include "geo/location.h"

namespace google
{

// ##########################################################

std::optional<geo::Location> GetClosestCoverage(const geo::Location& location);

// ##########################################################

class CoverageLookupError final : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

// ##########################################################

}