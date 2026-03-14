#pragma once
#include <nlohmann/json.hpp>
#include <filesystem>

namespace user
{

nlohmann::json LoadJsonFile(const std::filesystem::path& path);
void SaveJsonFile(const std::filesystem::path& path, const nlohmann::json& entries);

class JsonAccessError final : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

}