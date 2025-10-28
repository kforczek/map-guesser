#pragma once
#include <QString>


namespace geo
{

class Location
{
public:
    Location() = default;
    Location(double latitude, double longitude);

    // "lat: 123.123456, lng: 123.123456"
    [[nodiscard]] QString toHtmlStr() const;

    // "123.123456,123.123456"
    [[nodiscard]] std::string toUrlStr() const;

private:
    double m_latitude = 0;
    double m_longitude = 0;
};

}