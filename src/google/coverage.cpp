#include "google/coverage.h"

#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "google/token.h"

namespace
{

const std::string PROP_STATUS = "status";
const std::string PROP_LOCATION = "location";
const std::string PROP_LAT = "lat";
const std::string PROP_LNG = "lng";

const std::string STAT_LOC_FOUND = "OK";
const std::string STAT_LOC_NONE = "ZERO_RESULTS";


size_t curlWriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    auto* out = static_cast<std::string*>(userp);
    out->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

std::string callUrl(const std::string& url)
{
    CURL* curl = curl_easy_init();
    assert(curl);

    std::string response;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK)
        throw google::CoverageLookupError(curl_easy_strerror(res));

    curl_easy_cleanup(curl);
    return response;
}

nlohmann::json parseJson(const std::string& rawJson)
{
    auto json = nlohmann::json::parse(rawJson);
    if (json.is_discarded())
        throw google::CoverageLookupError("Failed to parse json response");

    return json;
}

std::optional<geo::Location> readLocation(const nlohmann::json& json)
{
    std::string status = json.value(PROP_STATUS, "ERR_NO_RESPONSE");
    if (status == STAT_LOC_NONE)
        return std::nullopt; // no coverage exists

    if (status != STAT_LOC_FOUND)
        throw google::CoverageLookupError("Coverage endpoint returned non-OK status: " + status);

    const auto& location = json[PROP_LOCATION];
    if (!location.is_object())
        throw google::CoverageLookupError("Coverage endpoint returned no location");

    double lat = location.value(PROP_LAT, 0.0);
    double lng = location.value(PROP_LNG, 0.0);

    if (lat == 0.0 && lng == 0.0)
        throw google::CoverageLookupError("Coverage endpoint returned invalid location");

    return geo::Location{lat, lng};
}

}

namespace google
{

std::optional<geo::Location> GetClosestCoverage(const geo::Location& location)
{
    const std::string url = "https://maps.googleapis.com/maps/api/streetview/metadata?location="
        + location.toUrlStr() + "&key=" + google::LoadApiToken();

    const std::string response = callUrl(url);

    auto json = parseJson(response);
    return readLocation(json);
}

}
