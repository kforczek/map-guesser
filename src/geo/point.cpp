#include "geo/point.h"
#include "planar/point.h"

#include "geo/consts.h"

#include <iomanip>
#include <sstream>

namespace
{

constexpr double MAX_DEG = 180;
constexpr double MAX_RAD = M_PI / 2;

void throwIfOutOfRange(double coord, double limit)
{
    if (coord > limit || coord < -limit)
    {
        throw std::invalid_argument("Coordinate " + std::to_string(coord)
                                    + "exceeds range [" + std::to_string(-limit) + ", " + std::to_string(limit) + "]");
    }
}

void enforceRange(const geo::Point& point)
{
    const double limit = (point.unit() == geo::UnitType::Degrees) ? MAX_DEG : MAX_RAD;

    throwIfOutOfRange(point.latitude(), limit);
    throwIfOutOfRange(point.longitude(), limit);
}

std::ostream& formatCoord(std::ostream& os)
{
    return os << std::fixed << std::setprecision(6);
}

double calcHaversineDistance(const geo::Point& loc1, const geo::Point& loc2)
{
    assert(loc1.unit() == geo::UnitType::Radians);
    assert(loc2.unit() == geo::UnitType::Radians);

    const double lat1 = loc1.latitude();
    const double lat2 = loc2.latitude();

    const double dLat = loc2.latitude() - loc1.latitude();
    const double dLon = loc2.longitude() - loc1.longitude();

    const double s = std::sin(dLat / 2.0);
    const double t = std::sin(dLon / 2.0);
    const double a = s * s + std::cos(lat1) * std::cos(lat2) * t * t;
    const double c = 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0 - a));

    return geo::EARTH_R * c;
}

}

namespace geo
{

Point::Point(double latitude, double longitude, UnitType unit)
    : m_latitude(latitude)
    , m_longitude(longitude)
    , m_unit(unit)
{
    enforceRange(*this);
}

double Point::latitude() const
{
    return m_latitude;
}

double Point::longitude() const
{
    return m_longitude;
}

UnitType Point::unit() const
{
    return m_unit;
}

double Point::distanceTo(const Point& other) const
{
    const Point radPt1 = this->toUnit(UnitType::Radians);
    const Point radPt2 = other.toUnit(UnitType::Radians);

    return calcHaversineDistance(radPt1, radPt2);
}

Point Point::toUnit(UnitType unit) const
{
    if (unit == m_unit)
        return *this;

    const double conv = (unit == UnitType::Radians) ? geo::DEG_TO_RAD : geo::RAD_TO_DEG;
    return Point{m_latitude * conv, m_longitude * conv, unit};
}

QString Point::toHtmlStr() const
{
    const Point degPt = this->toUnit(UnitType::Degrees);

    std::ostringstream formatter;
    formatter << "lat: ";
    formatter << formatCoord << degPt.latitude();
    formatter << ", lng: ";
    formatter << formatCoord << degPt.longitude();

    return formatter.str().c_str();
}

std::string Point::toUrlStr() const
{
    const Point degPt = this->toUnit(UnitType::Degrees);

    std::ostringstream formatter;
    formatter << formatCoord << degPt.latitude();
    formatter << ",";
    formatter << formatCoord << degPt.longitude();

    return formatter.str();
}

}
