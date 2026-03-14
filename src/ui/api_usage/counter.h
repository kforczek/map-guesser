#pragma once
#include <map>
#include "user/api_usage.h"

namespace ui::api_usage
{

// TODO: move this logic to user::settings
class Counter final
{
public:
    explicit Counter();

    bool isLimitReached(user::ApiCategory category) const;
    void logApiUsage(user::ApiCategory category);

    const std::map<user::ApiCategory, size_t>& getStats() const;

private:
    std::map<user::ApiCategory, size_t> m_currCounts;
};

}
