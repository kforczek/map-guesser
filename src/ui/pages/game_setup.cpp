#include "ui/pages/game_setup.h"

#include <qboxlayout.h>
#include <QMessageBox>

#include "ui/utils/map_file_access.h"
#include "lambert/projection.h"

namespace
{

constinit ui::widgets::PositiveNumberPropertyEditor::Values ROUNDS_COUNT_VALS{1, 5, 100};
constinit ui::widgets::PositiveNumberPropertyEditor::Values ROUND_POINTS_VALS{100, 1000, 1000000};

}

namespace ui::pages
{

GameSetupPage::GameSetupPage(QWidget* parent)
    : QFrame(parent)
    , m_propMap(new widgets::MapPropertyEditor(this))
    , m_propRoundsCnt(new widgets::PositiveNumberPropertyEditor(this, "Number of rounds", ROUNDS_COUNT_VALS))
    , m_propMaxRoundPoints(new widgets::PositiveNumberPropertyEditor(this, "Max round points", ROUND_POINTS_VALS))
    , m_startGameButton(new QPushButton("Start Game", this))
{
    auto* layout = new QVBoxLayout(this);
    setLayout(layout);

    layout->addStretch();
    layout->addWidget(m_propMap);
    layout->addWidget(m_propRoundsCnt);
    layout->addWidget(m_propMaxRoundPoints);
    layout->addStretch();
    layout->addWidget(m_startGameButton);

    connect(m_startGameButton, &QPushButton::clicked, this, &GameSetupPage::onStartGameButtonClicked);
}

void GameSetupPage::onStartGameButtonClicked()
{
    try
    {
        geo::Map geoMap = m_propMap->getValue();
        planar::Map projectedMap = lambert::project(geoMap);

        const unsigned int roundsCnt = m_propRoundsCnt->getValue();
        const unsigned int maxRoundPoints = m_propMaxRoundPoints->getValue();

        auto gameParams = std::make_shared<game::Params>();
        gameParams->geoMap = std::move(geoMap);
        gameParams->projectedMap = std::move(projectedMap);
        gameParams->roundsCnt = roundsCnt;
        gameParams->maxRoundPoints = maxRoundPoints;
        gameParams->playerNames.push_back("[Singleplayer]");

        emit startGame(std::move(gameParams));
    }
    catch (std::runtime_error& err)
    {
        QMessageBox::critical(this, "Invalid settings", err.what());
    }
}

}
