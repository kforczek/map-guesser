#pragma once
#include <filesystem>

namespace sv
{

// ##########################################################

/* Attempts to load API token from the default location */
const char* LoadApiToken();

// ##########################################################

class TokenLoadingError final : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

// ##########################################################

}
