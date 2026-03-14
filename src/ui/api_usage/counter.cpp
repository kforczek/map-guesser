#include "counter.h"

#include <QMessageBox>

#include "user/settings.h"

namespace
{

const std::unordered_set API_CATEGORIES{
    user::ApiCategory::StreetView,
    user::ApiCategory::Maps
};

}

namespace ui::api_usage
{

Counter::Counter()
{
    for (const auto category : API_CATEGORIES)
        m_currCounts[category] = user::CountMonthlyApiUsage(category);
}

const std::map<user::ApiCategory, size_t>& Counter::getStats() const
{
    return m_currCounts;
}

bool Counter::isLimitReached(user::ApiCategory category) const
{
    const size_t limit = user::settings::GetApiLimit(category);
    return limit > 0 && m_currCounts.at(category) >= limit;
}

void Counter::logApiUsage(user::ApiCategory category)
{
    if (user::settings::GetApiLimit(category) == 0)
        return;

    ++m_currCounts[category];
    user::LogApiUsage(category);

    assert(user::CountMonthlyApiUsage(category) <= user::settings::GetApiLimit(category));
}

}
