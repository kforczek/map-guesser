#pragma once
#include "geo/location.h"

namespace db
{

class LocationPool
{
public:
    // TODO: some representation of location regions etc.

    // TODO: serialization

    geo::Location center() const;
};

}
