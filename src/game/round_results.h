#pragma once
#include "defs.h"
#include "geo/point.h"

namespace game
{

struct Params;

// ###################################################################################################

struct PlayerRoundResult
{
    PlayerRoundResult(const geo::Point& actualLoc, const geo::Point& guessedLoc, const Params& gameParams);

    geo::Point guess;
    double distanceMeters = 0;
    unsigned int points = 0;
};

// ###################################################################################################

using TPlayer2Result = std::unordered_map<TPlayerName, PlayerRoundResult>;

struct RoundResults
{
    RoundResults(const geo::Point& correctLocation, const TPlayer2Guess& guesses, const Params& gameParams);

    geo::Point correctLocation;
    TPlayer2Result playerResults;
};

// ###################################################################################################

}