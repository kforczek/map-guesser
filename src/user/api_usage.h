#pragma once
#include <cstddef>
#include <expected>
#include <map>
#include <stdexcept>
#include <string>

namespace user
{

enum class ApiCategory
{
    StreetView,
    Maps
};

using Stats = std::map<ApiCategory, size_t>;

const Stats& GetApiUsageStats();
void LogApiUsage(ApiCategory category);

class ApiUsageAccessError final : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

}
