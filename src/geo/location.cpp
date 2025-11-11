#include "geo/location.h"

#include <iomanip>
#include <sstream>

namespace
{

std::ostream& formatCoord(std::ostream& os)
{
    return os << std::fixed << std::setprecision(6);
}

double calcHaversineDistance(const geo::Location& loc1, const geo::Location& loc2) {
    constexpr double R = 6371008.8; // mean Earth radius (meters)
    constexpr double toRad = M_PI / 180.0;

    double lat1 = loc1.latitude() * toRad;
    double lat2 = loc2.latitude() * toRad;
    double dLat = (loc2.latitude() - loc1.latitude()) * toRad;
    double dLon = (loc2.longitude() - loc1.longitude()) * toRad;

    double s = std::sin(dLat / 2.0);
    double t = std::sin(dLon / 2.0);
    double a = s * s + std::cos(lat1) * std::cos(lat2) * t * t;
    double c = 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0 - a));

    return R * c;
}

}

namespace geo
{

Location::Location(double latitude, double longitude)
    : m_latitude(latitude)
    , m_longitude(longitude) { }

double Location::latitude() const
{
    return m_latitude;
}

double Location::longitude() const
{
    return m_longitude;
}

double Location::distanceTo(const Location& other) const
{
    return calcHaversineDistance(*this, other);
}

QString Location::toHtmlStr() const
{
    std::ostringstream formatter;
    formatter << "lat: ";
    formatter << formatCoord << m_latitude;
    formatter << ", lng: ";
    formatter << formatCoord << m_longitude;

    return formatter.str().c_str();
}

std::string Location::toUrlStr() const
{
    std::ostringstream formatter;
    formatter << formatCoord << m_latitude;
    formatter << ",";
    formatter << formatCoord << m_longitude;

    return formatter.str();
}

}
