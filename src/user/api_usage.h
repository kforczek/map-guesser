#pragma once
#include <cstddef>
#include <expected>
#include <stdexcept>
#include <string>

namespace user
{

enum class ApiCategory
{
    StreetView,
    Maps
};

std::string ToString(ApiCategory category);
ApiCategory FromString(const std::string& str);

void LogApiUsage(ApiCategory category);
size_t CountMonthlyApiUsage(ApiCategory category);

class ApiUsageAccessError final : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

}
