#pragma once
#include <memory>
#include "engine.h"
#include "round_results.h"
#include "ui/bridge/commands.h"

namespace game
{

class MapGuesserGame final : public IEngineStateObserver
{
public:
    // game -> ui
    void setUiCommands(ui::bridge::Commands commands);

    // ui -> game
    void onCreateSession(Params&& gameParams);
    void onNextRoundRequested();
    void onPlayerFinishedRound(const std::optional<geo::Point>& guessedLocation);

    // session -> game
    void onRoundFinished() override;

private /*fields*/:
    std::unique_ptr<IEngine> m_gameEngine;
    std::vector<RoundResults> m_roundsHistory;

    ui::bridge::Commands m_uiCommands;

private /*methods*/:
    void startNextRound();
    void showGameSummary();
};

}