#include "settings.h"
#include "json.h"
#include "dir.h"
#include "util/unordered_bimap.h"

namespace
{
using namespace user;

std::filesystem::path SETTINGS_FILE_PATH;
const std::string JSON_KEY_API_LIMITS = "api_limits";

const util::unordered_bimap<ApiCategory, std::string> JSON_KEYS_API_CATEGORIES{
        {ApiCategory::StreetView, "StreetView"},
        {ApiCategory::Maps, "Maps"}
};

}

namespace cache
{

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
        const ApiCategory category = JSON_KEYS_API_CATEGORIES.right.at(item.key());
        apiLimits[category] = item.value().get<size_t>();
    }
}

void SetApiLimits(nlohmann::json& jsonData)
{
    nlohmann::json limitsJson = nlohmann::json::object();

    for (const auto& [category, limit] : apiLimits)
        limitsJson[JSON_KEYS_API_CATEGORIES.left.at(category)] = limit;

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