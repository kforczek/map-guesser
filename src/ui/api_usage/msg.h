#pragma once
#include <map>
#include "user/api_usage.h"

class QWidget;

namespace ui::api_usage
{

void ShowInfo(QWidget* parent, const std::map<user::ApiCategory, size_t>& stats);
void HandleWarnings(QWidget* parent, const std::map<user::ApiCategory, size_t>& stats);

}
