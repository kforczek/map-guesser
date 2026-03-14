#pragma once
#include "api_usage.h"

namespace user::settings
{

void Load();
void Save();

size_t GetApiLimit(ApiCategory category);
void SetApiLimit(ApiCategory category, size_t limit);

}