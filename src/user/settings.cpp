#include "settings.h"
#include "json.h"
#include "dir.h"
#include "util/unordered_bimap.h"

namespace
{
using namespace user;
using namespace user::settings;

std::filesystem::path SETTINGS_FILE_PATH;
const std::string KEY_API_LIMIT_STREET_VIEW = "api_limit_streetview";
const std::string KEY_API_LIMIT_MAPS = "api_limit_maps";

}

namespace cache
{

// ######################################################################################

Values data;

// ######################################################################################

void LoadApiLimits(const nlohmann::json& jsonData)
{
    if (const auto svLimitIt = jsonData.find(KEY_API_LIMIT_STREET_VIEW); svLimitIt != jsonData.end())
        data.apiStreetViewLimit = svLimitIt->get<size_t>();

    if (const auto mapsLimitIt = jsonData.find(KEY_API_LIMIT_MAPS); mapsLimitIt != jsonData.end())
        data.apiMapsLimit = mapsLimitIt->get<size_t>();
}

void SetApiLimits(nlohmann::json& jsonData)
{
    jsonData[KEY_API_LIMIT_STREET_VIEW] = data.apiStreetViewLimit;
    jsonData[KEY_API_LIMIT_MAPS] = data.apiMapsLimit;
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

const Values& Get()
{
    return cache::data;
}

void Set(Values&& data)
{
    cache::data = std::move(data);
}

Values Defaults()
{
    return Values{};
}

size_t GetApiLimit(ApiCategory category)
{
    return (category == ApiCategory::StreetView) ? cache::data.apiStreetViewLimit : cache::data.apiMapsLimit;
}

}