#include "json.h"
#include <fstream>

namespace user
{

nlohmann::json LoadJsonFile(const std::filesystem::path& path)
{
    auto entries = nlohmann::json::array();
    if (!std::filesystem::exists(path))
        return entries;

    std::ifstream in{path};
    if (!in)
        throw JsonAccessError{"Cannot open log file for reading: " + path.string()};

    if (in.peek() != std::ifstream::traits_type::eof())
        in >> entries;

    return entries;
}

// #################################################################################################

void SaveJsonFile(const std::filesystem::path& path, const nlohmann::json& entries)
{
    std::ofstream out{path};
    if (!out)
        throw JsonAccessError{"Cannot open log file for writing: " + path.string()};

    out << entries.dump(2) << '\n';
}

}
