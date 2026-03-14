#pragma once
#include "api_usage.h"

namespace user::settings
{

struct Values
{
    size_t apiStreetViewLimit = 0;
    size_t apiMapsLimit = 0;

    bool operator==(const Values& settings_data) const = default;
};

void Load();
void Save();

Values Get();
void Set(const Values& data);

size_t GetApiLimit(ApiCategory category);
void SetApiLimit(ApiCategory category, size_t limit);

}