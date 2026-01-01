#pragma once
#include <vector>
#include "triangle.h"

namespace planar
{

class Region;

std::vector<Triangle> Triangulate(const std::vector<Region>& regions);

}