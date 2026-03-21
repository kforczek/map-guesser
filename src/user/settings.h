#pragma once
#include "api_usage.h"

namespace user::settings
{

struct Values
{
    size_t apiStreetViewLimit = 5'000;
    size_t apiMapsLimit = 10'000;

    bool operator==(const Values& settings_data) const = default;
};

void Load();
void Save();

const Values& Get();
void Set(Values&& data);
Values Defaults();

size_t GetApiLimit(ApiCategory category);

}