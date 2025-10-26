#pragma once
#include <QString>


namespace geo
{

class Location
{
public:
    Location(double latitude, double longitude);

    QString toStr() const;

private:
    double m_latitude = 0;
    double m_longitude = 0;
};

}