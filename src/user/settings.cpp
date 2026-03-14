#include "settings.h"

#include <unordered_map>
#include "json.h"
#include "dir.h"

namespace
{
std::filesystem::path SETTINGS_FILE_PATH;
const std::string JSON_KEY_API_LIMITS = "api_limits";
}

namespace cache
{
using namespace user;

// ######################################################################################

std::unordered_map<user::ApiCategory, size_t> apiLimits{
            {user::ApiCategory::StreetView, 5000},
            {user::ApiCategory::Maps, 10000}
};

// ######################################################################################

void LoadApiLimits(const nlohmann::json& jsonData)
{
    if (!jsonData.contains(JSON_KEY_API_LIMITS))
        return;

    for (const auto& item : jsonData.at(JSON_KEY_API_LIMITS).items())
    {
        const ApiCategory category = FromString(item.key());
        apiLimits[category] = item.value().get<size_t>();
    }
}

void SetApiLimits(nlohmann::json& jsonData)
{
    nlohmann::json limitsJson = nlohmann::json::object();

    for (const auto& [category, limit] : apiLimits)
        limitsJson[ToString(category)] = limit;

    jsonData[JSON_KEY_API_LIMITS] = std::move(limitsJson);
}

}

namespace user::settings
{

void Load()
{
    SETTINGS_FILE_PATH = user::GetUserDirPath() / "settings.json";

    if (!std::filesystem::exists(SETTINGS_FILE_PATH))
        return;

    const nlohmann::json jsonData = LoadJsonFile(SETTINGS_FILE_PATH);

    cache::LoadApiLimits(jsonData);
}

void Save()
{
    nlohmann::json jsonData;

    cache::SetApiLimits(jsonData);

    SaveJsonFile(SETTINGS_FILE_PATH, jsonData);
}

Values Get()
{
    Values data;
    data.apiStreetViewLimit = cache::apiLimits.at(ApiCategory::StreetView);
    data.apiMapsLimit = cache::apiLimits.at(ApiCategory::Maps);
    return data;
}

void Set(const Values& data)
{
    cache::apiLimits.at(ApiCategory::StreetView) = data.apiStreetViewLimit;
    cache::apiLimits.at(ApiCategory::Maps) = data.apiMapsLimit;
}

size_t GetApiLimit(ApiCategory category)
{
    return cache::apiLimits.at(category);
}

void SetApiLimit(ApiCategory category, size_t limit)
{
    cache::apiLimits.at(category) = limit;
}

}