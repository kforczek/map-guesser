#pragma once
#include <filesystem>
#include <QString>

namespace sv
{

// TODO use
class TokenLoadingError final: public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

/* Attempts to load API token from the default location */
QString LoadApiToken();

}
