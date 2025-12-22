#pragma once
#include "geo/point.h"

namespace db
{

class LocationPool
{
public:
    // TODO: some representation of location regions etc.

    // TODO: serialization

    geo::Point center() const;
};

}
