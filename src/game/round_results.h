#pragma once
#include "defs.h"
#include "geo/point.h"

namespace game
{

struct Params;

// ###################################################################################################

struct PlayerRoundResult
{
    // Incremental mode - points change = points for distance
    PlayerRoundResult(const geo::Point& actualLoc, const geo::Point& guessedLoc, const Params& gameParams);

    // TODO: ctor for duel/deathmatch

    geo::Point guess;
    double distanceMeters = 0;

    unsigned int distancePoints = 0;
    int pointsChange = 0;
};

// ###################################################################################################

using TPlayer2Result = std::unordered_map<TPlayerName, PlayerRoundResult>;

// TODO [naming] -> RoundResult
struct RoundResults
{
    RoundResults(const geo::Point& correctLocation, const TPlayer2Guess& guesses, const Params& gameParams);

    geo::Point correctLocation;
    TPlayer2Result playerResults;
};

// ###################################################################################################

}