#include "msg.h"

#include <QMessageBox>
#include <QString>
#include <sstream>
#include <unordered_map>

#include "user/settings.h"

namespace
{

std::map<user::ApiCategory, size_t> STATS_AT_LAST_WARNING;

const std::unordered_map<user::ApiCategory, std::string> API_CATEGORY_TO_STRING = {
    {user::ApiCategory::StreetView, "Street View"},
    {user::ApiCategory::Maps, "Maps"}
};

bool isNewThresholdCrossed(size_t currUsageCnt, size_t lastUsageCnt, size_t limit)
{
    if (limit == 0)
        return false;

    const double usagePct = (static_cast<double>(currUsageCnt) / static_cast<double>(limit)) * 100.0;

    if (usagePct >= 90.0 && lastUsageCnt != currUsageCnt)
        return true;

    if (usagePct >= 75.0 && usagePct < 90.0 && lastUsageCnt < (limit * 75 / 100))
        return true;

    if (usagePct >= 50.0 && usagePct < 75.0 && lastUsageCnt < (limit * 50 / 100))
        return true;

    return false;
}

void showWarning(QWidget* parent, user::ApiCategory category, size_t currUsage)
{
    const size_t limit = user::settings::GetApiLimit(category);
    const double usagePct = (static_cast<double>(currUsage) / limit) * 100.0;

    const auto msg = QString("%1 API used in %2% (%3 of %4 loads).")
                        .arg(API_CATEGORY_TO_STRING.at(category).c_str())
                        .arg(usagePct, 0, 'f', 0)
                        .arg(currUsage)
                        .arg(limit);

    QMessageBox::warning(parent, "API usage this month", msg);
}

}

namespace ui::api_usage
{

void ShowInfo(QWidget* parent)
{
    std::stringstream ss;
    ss.imbue(std::locale{""});

    ss << "API usage this month:\n\n";
    for (const auto& [category, currUsage] : user::GetApiUsageStats())
    {
        const size_t limit = user::settings::GetApiLimit(category);
        ss << "  " << API_CATEGORY_TO_STRING.at(category) << ": " << currUsage << " of " << limit << std::endl;
    }

    QMessageBox::information(parent, "API usage stats", ss.str().c_str());
}

void HandleWarnings(QWidget* parent)
{
    for (const auto& [category, currUsage] : user::GetApiUsageStats())
    {
        const size_t limit = user::settings::GetApiLimit(category);
        if (isNewThresholdCrossed(currUsage, STATS_AT_LAST_WARNING[category], limit))
            showWarning(parent, category, currUsage);
    }

    STATS_AT_LAST_WARNING = user::GetApiUsageStats();
}

}