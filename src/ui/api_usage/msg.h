#pragma once
#include <map>
#include "user/api_usage.h"

class QWidget;

namespace ui::api_usage
{

void ShowInfo(QWidget* parent);
void HandleWarnings(QWidget* parent);

}
