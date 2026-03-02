#pragma once
#include <filesystem>

namespace user
{

const std::filesystem::path& GetUserDirPath();
void SetUserDirPath(std::filesystem::path rootPath);

}
