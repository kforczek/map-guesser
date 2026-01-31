#pragma once
#include <filesystem>
#include <stdexcept>

#include "geo/map.h"

namespace ui::utils
{

geo::Map LoadMapFromFile(const QString& path);
void SaveMapToFile(const geo::Map& map, const QString& path);

// #####################################################

struct MapFileAccessError final : std::runtime_error
{
    using std::runtime_error::runtime_error;
};

}
