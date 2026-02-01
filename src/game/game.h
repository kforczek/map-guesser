#pragma once
#include "session.h"
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
    void onCreateSession(std::shared_ptr<Params> gameParams);
    void onStartNextRound();
    void onGuessSubmitted(const geo::Point& guessedLocation);

    // session -> game
    void onRoundFinished(const RoundResults &roundResults) const override;

private:
    std::optional<Session> m_gameSession;
    ui::bridge::Commands m_uiCommands;
};

}