#pragma once
#include "session.h"
#include "round_results.h"
#include "mode/observer.h"
#include "ui/bridge/commands.h"

namespace game
{

class MapGuesserGame final : public game::mode::IGameStateObserver
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
    std::optional<Session> m_gameSession;
    std::vector<RoundResults> m_roundsHistory;

    ui::bridge::Commands m_uiCommands;

private /*methods*/:
    void startNextRound();
    void showGameSummary();
};

}