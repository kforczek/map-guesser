#include "api_usage.h"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <string>
#include <string_view>

#include <nlohmann/json.hpp>

#include "dir.h"
#include "json.h"

namespace chr = std::chrono;

namespace
{

using namespace user;

const std::string PACIFIC_TIMEZONE_NAME = "America/Los_Angeles";

// #################################################################################################

class Timestamp
{
public:
    explicit Timestamp(chr::local_seconds localTime);

    static Timestamp now();
    static Timestamp fromString(const std::string& rawStr);
    std::string toString() const;

    bool isCurrentPacificMonth() const;
    chr::zoned_time<chr::seconds> toPacific() const;

private:
    chr::local_seconds m_localTime;

    chr::year_month toPacificYearMonth() const;
};

Timestamp::Timestamp(chr::local_seconds localTime)
    : m_localTime(localTime) {}

/*static*/ Timestamp Timestamp::now()
{
    const auto now = chr::time_point_cast<chr::seconds>(chr::system_clock::now());
    return Timestamp{chr::local_seconds{now.time_since_epoch()}};
}

/*static*/ Timestamp Timestamp::fromString(const std::string& rawStr)
{
    chr::local_seconds tp;
    std::istringstream ss{rawStr};
    ss >> chr::parse("%FT%T", tp);
    if (ss.fail())
        throw ApiUsageAccessError{
            std::format("Malformed timestamp: \"{}\"", rawStr)
        };

    return Timestamp{tp};
}

std::string Timestamp::toString() const
{
    return std::format("{:%FT%T}", m_localTime);
}

bool Timestamp::isCurrentPacificMonth() const
{
    return toPacificYearMonth() == Timestamp::now().toPacificYearMonth();
}

std::chrono::zoned_time<std::chrono::seconds> Timestamp::toPacific() const
{
    const auto* localZone   = chr::current_zone();
    const auto* pacificZone = chr::locate_zone(PACIFIC_TIMEZONE_NAME);

    const chr::zoned_time localZoned{localZone, m_localTime};
    const chr::sys_time<chr::seconds> utc = localZoned.get_sys_time();

    return chr::zoned_time{pacificZone, utc};
}

chr::year_month Timestamp::toPacificYearMonth() const
{
    const auto pacificNow = chr::floor<chr::days>(toPacific().get_local_time());
    const chr::year_month_day pacificNowYmd{pacificNow};

    return chr::year_month{pacificNowYmd.year(), pacificNowYmd.month()};
}

// #################################################################################################

class ApiUsageEntry
{
public:
    ApiUsageEntry(Timestamp timestamp, ApiCategory apiCategory);

    ApiCategory apiCategory() const;
    bool isCurrentPacificMonth() const;

    static ApiUsageEntry fromJson(const nlohmann::json& json);
    nlohmann::json toJson() const;

private:
    Timestamp m_timestamp;
    ApiCategory m_apiCategory;
};

ApiUsageEntry::ApiUsageEntry(Timestamp timestamp, ApiCategory apiCategory)
    : m_timestamp(timestamp)
    , m_apiCategory(apiCategory) { }

ApiCategory ApiUsageEntry::apiCategory() const
{
    return m_apiCategory;
}

bool ApiUsageEntry::isCurrentPacificMonth() const
{
    return m_timestamp.isCurrentPacificMonth();
}

/*static*/ ApiUsageEntry ApiUsageEntry::fromJson(const nlohmann::json& json)
{
    if (!json.is_object())
        throw ApiUsageAccessError{"ApiUsageEntry JSON must be an object"};

    if (!json.contains("timestamp") || !json["timestamp"].is_string())
        throw ApiUsageAccessError{"Missing or invalid \"timestamp\" field"};

    if (!json.contains("api_category") || !json["api_category"].is_string())
        throw ApiUsageAccessError{"Missing or invalid \"api_category\" field"};

    const auto timestampStr = json["timestamp"].get<std::string>();
    const auto categoryStr  = json["api_category"].get<std::string>();

    const Timestamp timestamp = Timestamp::fromString(timestampStr);
    const ApiCategory apiCategory = FromString(categoryStr);

    return ApiUsageEntry{timestamp, apiCategory};
}

nlohmann::json ApiUsageEntry::toJson() const
{
    return {
        {"timestamp", m_timestamp.toString()},
        {"api_category", ToString(m_apiCategory)}
    };
}

// #################################################################################################

std::filesystem::path BuildLogFilePath()
{
    static const std::string LOG_FILE_NAME = "api_usage.json";
    return GetUserDirPath() / LOG_FILE_NAME;
}

// #################################################################################################

}

namespace user
{

std::string ToString(ApiCategory category)
{
    static const std::unordered_map<ApiCategory, std::string> API_CATEGORIES_TO_STR{
        {ApiCategory::StreetView, "StreetView"},
        {ApiCategory::Maps, "Maps"}
    };

    return API_CATEGORIES_TO_STR.at(category);
}

ApiCategory FromString(const std::string& str)
{
    static const std::unordered_map<std::string, ApiCategory> STR_TO_API_CATEGORIES{
        {"StreetView", ApiCategory::StreetView},
        {"Maps", ApiCategory::Maps}
    };

    return STR_TO_API_CATEGORIES.at(str);
}

void LogApiUsage(ApiCategory category)
{
    const std::filesystem::path logPath = BuildLogFilePath();
    nlohmann::json entries = LoadJsonFile(logPath);

    const ApiUsageEntry newEntry{Timestamp::now(), category};
    entries.push_back(newEntry.toJson());

    SaveJsonFile(logPath, entries);
}

size_t CountMonthlyApiUsage(ApiCategory category)
{
    const std::filesystem::path logPath = BuildLogFilePath();
    if (!std::filesystem::exists(logPath))
        return 0;

    nlohmann::json entries = LoadJsonFile(logPath);

    size_t count = 0;

    for (const auto& jsonEntry : entries)
    {
        ApiUsageEntry entry = ApiUsageEntry::fromJson(jsonEntry);
        if (entry.apiCategory() != category)
            continue;

        if (!entry.isCurrentPacificMonth())
            continue;

        ++count;
    }

    return count;
}

}
