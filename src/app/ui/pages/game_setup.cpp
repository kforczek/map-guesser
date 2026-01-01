#include "app/ui/pages/game_setup.h"

#include <QMessageBox>

#include "app/ui/map_file_access.h"
#include "lambert/projection.h"

namespace app::ui::pages
{

GameSetupPage::GameSetupPage(QWidget* parent)
    : QFrame(parent)
    , m_layout(this)
    , m_propMapPath(this)
    , m_startGameButton("Start Game", this)
{
    setLayout(&m_layout);

    m_layout.addWidget(&m_propMapPath);
    m_layout.addWidget(&m_startGameButton);

    connect(&m_startGameButton, &QPushButton::clicked, this, &GameSetupPage::onStartGameButtonClicked);
}

void GameSetupPage::onStartGameButtonClicked()
{
    try
    {
        const geo::Map geoMap = LoadMapFromFile(m_propMapPath.getValue());
        planar::Map projectedMap = lambert::project(geoMap);

        game::Params gameParams{geoMap.center(), std::move(projectedMap)};
        emit startGame(std::move(gameParams));
    }
    catch (std::runtime_error& err)
    {
        QMessageBox::critical(this, "Invalid settings", err.what());
    }
}

}
