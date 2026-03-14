#include "limit.h"

#include <QMessageBox>

#include "user/settings.h"

namespace
{

const std::unordered_map<user::ApiCategory, QString> API_CATEGORY_TO_STR{
    {user::ApiCategory::StreetView, "Street View"},
    {user::ApiCategory::Maps, "Maps"}
};

}

namespace ui::api_usage
{

bool IsLimitReached(user::ApiCategory category)
{
    const size_t limit = user::settings::GetApiLimit(category);
    return limit > 0 && user::GetApiUsageStats().at(category) >= limit;
}

bool TryLogUsage(QWidget* parent, user::ApiCategory category)
{
    if (IsLimitReached(category))
    {
        const QString categoryName = API_CATEGORY_TO_STR.at(category);
        QMessageBox::critical(parent, categoryName, "You have reached the limit of " + categoryName + " API usage.");
        return false;
    }

    user::LogApiUsage(category);
    return true;
}

}
