#pragma once
#include <QString>


namespace geo
{

enum class UnitType
{
    Degrees,
    Radians
};

class Point
{
public:
    Point() = default;
    Point(double latitude, double longitude, UnitType unit);

    double latitude() const;
    double longitude() const;
    UnitType unit() const;

    // Distance in meters
    double distanceTo(const Point& other) const;

    // Point converted to the desired unit
    Point toUnit(UnitType unit) const;

    // Formatted for HTML usages (always in degrees!): "lat: 123.123456, lng: 123.123456"
    QString toHtmlStr() const;

    // Formatted for URL usages (always in degrees!): "123.123456,123.123456"
    std::string toUrlStr() const;

private:
    double m_latitude = 0;
    double m_longitude = 0;
    UnitType m_unit = UnitType::Degrees;
};

}