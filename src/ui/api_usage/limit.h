#pragma once
#include "user/api_usage.h"

class QWidget;

namespace ui::api_usage
{

bool IsLimitReached(user::ApiCategory category);
bool TryLogUsage(QWidget* parent, user::ApiCategory category);

}
