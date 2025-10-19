#include "token.h"

namespace
{

// TODO: actual save/load for user tokens
const QString API_TOKEN = "SECRET";

}

namespace sv
{

QString LoadApiToken()
{
    return API_TOKEN;
}

}