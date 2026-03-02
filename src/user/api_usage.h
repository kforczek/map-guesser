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

void LogApiUsage(ApiCategory category);
size_t GetApiUsageCount(ApiCategory category);

class ApiUsageAccessError final : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

}
