#include "location.h"

#include <iomanip>
#include <sstream>

namespace
{

std::ostream& formatCoord(std::ostream& os)
{
    return os << std::fixed << std::setprecision(6);
}

}

namespace geo
{

Location::Location(double latitude, double longitude)
    : m_latitude(latitude)
    , m_longitude(longitude) { }

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
