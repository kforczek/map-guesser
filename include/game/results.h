#pragma once

namespace db
{
class LocationPool;
}

namespace geo
{
class Location;
}

namespace game
{

class RoundResults
{
public:
    RoundResults(const db::LocationPool& locPool, const geo::Location& actualLoc, const geo::Location& guessedLoc);

    double distanceMeters() const;
    unsigned int points() const;

private:
    double m_distanceMeters = 0;
    unsigned int m_points = 0;
};

}