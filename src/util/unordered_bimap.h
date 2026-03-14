#pragma once
#include <unordered_map>

namespace util
{

template <typename T1, typename T2>
struct unordered_bimap
{
    std::unordered_map<T1, T2> left;
    std::unordered_map<T2, T1> right;

    unordered_bimap() = default;
    unordered_bimap(std::initializer_list<std::pair<T1, T2>> init)
    {
        left.reserve(init.size());
        right.reserve(init.size());
        for (auto& [l, r] : init)
        {
            left.emplace(l, r);
            right.emplace(std::move(r), std::move(l));
        }
    }
};

}
