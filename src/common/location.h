#pragma once
#include <QString>


class Location
{

public:
    QString toStr() const {return "";} // TODO

private:
    double m_latitude = 0;
    double m_longitude = 0;
};

