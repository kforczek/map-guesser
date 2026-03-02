#include "api_usage.h"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <string>
#include <string_view>

#include <nlohmann/json.hpp>

#include "dir.h"

namespace chr = std::chrono;

namespace
{

using namespace user;

const std::string PACIFIC_TIMEZONE_NAME = "America/Los_Angeles";

const std::unordered_map<ApiCategory, std::string> API_CATEGORIES_TO_STR{
    {ApiCategory::StreetView, "StreetView"},
    {ApiCategory::Maps, "Maps"}
};

const std::unordered_map<std::string, ApiCategory> STR_TO_API_CATEGORIES{
        {"StreetView", ApiCategory::StreetView},
        {"Maps", ApiCategory::Maps}
};

// #################################################################################################

class Timestamp
{
public:
    explicit Timestamp(chr::local_seconds localTime);

    static Timestamp now();
    static Timestamp fromString(const std::string& rawStr);
    std::string toString() const;

    chr::zoned_time<chr::seconds> toPacific() const;

private:
    chr::local_seconds m_localTime;
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

std::chrono::zoned_time<std::chrono::seconds> Timestamp::toPacific() const
{
    const auto* localZone   = chr::current_zone();
    const auto* pacificZone = chr::locate_zone("America/Los_Angeles");

    const chr::zoned_time localZoned{localZone, m_localTime};
    const chr::sys_time<chr::seconds> utc = localZoned.get_sys_time();

    return chr::zoned_time{pacificZone, utc};
}

// #################################################################################################

class ApiUsageEntry
{
public:
    static ApiUsageEntry fromJson(const nlohmann::json& json);
    nlohmann::json toJson() const;

private:
    ApiUsageEntry(Timestamp timestamp, ApiCategory apiCategory);

    Timestamp m_timestamp;
    ApiCategory m_apiCategory;
};

ApiUsageEntry::ApiUsageEntry(Timestamp timestamp, ApiCategory apiCategory)
    : m_timestamp(timestamp)
    , m_apiCategory(apiCategory) { }

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

    const auto apiCategoryIt = STR_TO_API_CATEGORIES.find(categoryStr);
    if (apiCategoryIt == STR_TO_API_CATEGORIES.end())
    {
        throw ApiUsageAccessError{
            std::format("Unknown api_category: \"{}\"", categoryStr)
        };
    }

    return ApiUsageEntry{timestamp, apiCategoryIt->second};
}

nlohmann::json ApiUsageEntry::toJson() const
{
    return {
    {"timestamp", m_timestamp.toString()},
    {"api_category", API_CATEGORIES_TO_STR.at(m_apiCategory)}
    };
}

// #################################################################################################


// #################################################################################################

nlohmann::json LoadJsonFile(const std::filesystem::path& path)
{
    auto entries = nlohmann::json::array();
    if (!std::filesystem::exists(path))
        return entries;

    std::ifstream in{path};
    if (!in)
        throw ApiUsageAccessError{"Cannot open log file for reading: " + path.string()};
    
    if (in.peek() != std::ifstream::traits_type::eof())
        in >> entries;

    if (!entries.is_array())
        throw ApiUsageAccessError{"Log file does not contain a JSON array."};

    return entries;
}

// #################################################################################################

void SaveJsonFile(const std::filesystem::path& path, const nlohmann::json& entries)
{
    std::ofstream out{path};
    if (!out)
        throw ApiUsageAccessError{"Cannot open log file for writing: " + path.string()};

    out << entries.dump(2) << '\n';
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

void LogApiUsage(ApiCategory category)
{
    const std::filesystem::path logPath = BuildLogFilePath();
    nlohmann::json entries = LoadJsonFile(logPath);

    entries.push_back({
        {"category",  category},
        {"timestamp", Timestamp::now().toString()}
    });

    SaveJsonFile(logPath, entries);
}

size_t GetApiUsageCount(ApiCategory category)
{
    const std::filesystem::path logPath = BuildLogFilePath();
    if (!std::filesystem::exists(logPath))
        return 0;

    nlohmann::json entries = LoadJsonFile(logPath);

    const auto pacific_now = Timestamp::now().toPacific();
    const auto now_days =
        chr::floor<chr::days>(pacific_now.get_local_time());
    const chr::year_month_day now_ymd{now_days};
    const chr::year_month current_pacific_ym{
        now_ymd.year(), now_ymd.month()
    };

    std::size_t count = 0;

    for (const auto& entry : entries)
    {
        if (!entry.contains("category") || !entry.contains("timestamp"))
            continue;

        if (entry["category"].get<std::string>() !=
            API_CATEGORIES_TO_STR.at(category))
            continue;

        Timestamp ts =
            Timestamp::fromString(entry["timestamp"].get<std::string>());

        const auto pacific = ts.toPacific();
        const auto entry_days =
            chr::floor<chr::days>(pacific.get_local_time());
        const chr::year_month_day entry_ymd{entry_days};
        const chr::year_month entry_pacific_ym{
            entry_ymd.year(), entry_ymd.month()
        };

        if (entry_pacific_ym == current_pacific_ym)
            ++count;
    }

    return count;
}

}
