#include "location.h"

#include <iomanip>
#include <sstream>

namespace geo
{

Location::Location(const double latitude, const double longitude)
    : m_latitude(latitude)
    , m_longitude(longitude) { }

QString Location::toStr() const
{
    std::ostringstream formatter;
    formatter << "lat: ";
    formatter << std::fixed << std::setprecision(6) << m_latitude;
    formatter << ", lng: ";
    formatter << std::fixed << std::setprecision(6) << m_longitude;

    return formatter.str().c_str();
}

}
