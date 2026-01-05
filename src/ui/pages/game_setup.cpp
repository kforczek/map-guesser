#include "ui/pages/game_setup.h"

#include <QMessageBox>

#include "ui/map_file_access.h"
#include "lambert/projection.h"

namespace ui::pages
{

GameSetupPage::GameSetupPage(QWidget* parent)
    : QFrame(parent)
    , m_layout(this)
    , m_propMap(this)
    , m_propMaxRoundPoints(this, "Max round points", 1000)
    , m_startGameButton("Start Game", this)
{
    setLayout(&m_layout);

    m_layout.addStretch();
    m_layout.addWidget(&m_propMap);
    m_layout.addWidget(&m_propMaxRoundPoints);
    m_layout.addStretch();
    m_layout.addWidget(&m_startGameButton);

    connect(&m_startGameButton, &QPushButton::clicked, this, &GameSetupPage::onStartGameButtonClicked);
}

void GameSetupPage::onStartGameButtonClicked()
{
    try
    {
        geo::Map geoMap = m_propMap.getValue();
        planar::Map projectedMap = lambert::project(geoMap);

        const unsigned int maxRoundPoints = m_propMaxRoundPoints.getValue();

        game::Params gameParams{std::move(geoMap), std::move(projectedMap), maxRoundPoints};
        emit startGame(std::move(gameParams));
    }
    catch (std::runtime_error& err)
    {
        QMessageBox::critical(this, "Invalid settings", err.what());
    }
}

}
