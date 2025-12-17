#include "google/token.h"

namespace
{

const char* ENV_VAR_NAME = "MAP_GUESSER_API_TOKEN";

}

namespace google
{

const char* LoadApiToken()
{
    const char* token = std::getenv(ENV_VAR_NAME);
    if (!token)
        throw TokenLoadingError(std::string("No token is set under env variable ") + ENV_VAR_NAME);

    return token;
}

}