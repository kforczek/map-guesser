#include "counter.h"

#include <QMessageBox>

#include "user/settings.h"

namespace
{

const std::unordered_set API_CATEGORIES{
    user::ApiCategory::StreetView,
    user::ApiCategory::Maps
};

bool isNewThresholdCrossed(size_t currUsageCnt, size_t lastUsageCnt, size_t limit)
{
    const double usagePct = (static_cast<double>(currUsageCnt) / static_cast<double>(limit)) * 100.0;

    if (usagePct >= 90.0)
        return true;

    if (usagePct >= 75.0 && usagePct < 90.0 && lastUsageCnt < (limit * 75 / 100))
        return true;

    if (usagePct >= 50.0 && usagePct < 75.0 && lastUsageCnt < (limit * 50 / 100))
        return true;

    return false;
}

}

namespace ui::api_usage
{

Counter::Counter(QWidget* parent)
    : QWidget(parent)
{
    for (const auto category : API_CATEGORIES)
        m_currCounts[category] = user::CountMonthlyApiUsage(category);
}

void Counter::handleWarnings()
{
    for (const auto category : API_CATEGORIES)
    {
        const size_t limit = user::settings::GetApiLimit(category);
        if (limit == 0)
            continue;

        if (isNewThresholdCrossed(m_currCounts[category], m_countsAtLastWarning[category], limit))
            showWarning(category);
    }

    m_countsAtLastWarning = m_currCounts;
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

void Counter::showWarning(user::ApiCategory category)
{
    static const std::unordered_map<user::ApiCategory, QString> API_CATEGORY_TO_STRING = {
        {user::ApiCategory::StreetView, "Street View"},
        {user::ApiCategory::Maps, "Maps"}
    };

    const size_t limit = user::settings::GetApiLimit(category);
    const size_t usageCnt = m_currCounts[category];
    const double usagePct = (static_cast<double>(usageCnt) / limit) * 100.0;

    const auto msg = QString("%1 API used in %2% (%3 of %4 loads).")
                        .arg(API_CATEGORY_TO_STRING.at(category))
                        .arg(usagePct, 0, 'f', 0)
                        .arg(usageCnt)
                        .arg(limit);

    QMessageBox::warning(this, "API usage this month", msg);
}

}
