#pragma once
#include <QWidget>
#include "user/api_usage.h"

namespace ui::api_usage
{

class Counter final : public QWidget
{
public:
    explicit Counter(QWidget* parent);

    bool isLimitReached(user::ApiCategory category) const;
    void logApiUsage(user::ApiCategory category);

    void handleWarnings();

private:
    std::unordered_map<user::ApiCategory, size_t> m_currCounts;
    std::unordered_map<user::ApiCategory, size_t> m_countsAtLastWarning;

    void showWarning(user::ApiCategory category);
};

}
