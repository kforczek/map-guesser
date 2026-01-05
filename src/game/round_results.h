#pragma once

namespace geo
{
class Point;
}

namespace game
{

struct Params;

class RoundResults
{
public:
    RoundResults(const geo::Point& actualLoc, const geo::Point& guessedLoc, const Params& gameParams);

    double distanceMeters() const;
    unsigned int points() const;

private:
    double m_distanceMeters = 0;
    unsigned int m_points = 0;
};

}