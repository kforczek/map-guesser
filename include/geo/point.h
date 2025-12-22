#pragma once
#include <QString>


namespace geo
{

class Point
{
public:
    Point() = default;
    Point(double latitude, double longitude);

    double latitude() const;
    double longitude() const;

    // Distance in meters
    double distanceTo(const Point& other) const;

    // "lat: 123.123456, lng: 123.123456"
    QString toHtmlStr() const;

    // "123.123456,123.123456"
    std::string toUrlStr() const;

private:
    double m_latitude = 0;
    double m_longitude = 0;
};

}