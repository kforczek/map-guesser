#include "dir.h"

#include <cassert>

namespace
{

std::filesystem::path s_userDir;

}

namespace user
{

const std::filesystem::path& GetUserDirPath()
{
    assert(s_userDir != std::filesystem::path{});
    assert(std::filesystem::exists(s_userDir));
    return s_userDir;
}

void SetUserDirPath(std::filesystem::path rootPath)
{
    s_userDir = std::move(rootPath);
    std::filesystem::create_directories(s_userDir);
}

}