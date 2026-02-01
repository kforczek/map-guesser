#include "ui/pages/round_results.h"
#include "../../game/round_results.h"

namespace ui::pages
{

// ReSharper disable CppMemberFunctionMayBeConst

RoundResultsPage::RoundResultsPage(QWidget* parent)
    : QFrame(parent)
    , m_layout(new QVBoxLayout(this))
    , m_distanceLabel(new QLabel(this))
    , m_pointsLabel(new QLabel(this))
    , m_distanceMap(new google::DistanceMap(this))
    , m_proceedButton(new QPushButton("Next Round", this))
{
    setupLayout();
    setupInfoLabels();
    setupDistanceMap();
    setupContinueButton();
    setupBottomSpacing();
}

void RoundResultsPage::setCenter(const geo::Point& center)
{
    m_distanceMap->setCenter(center);
}

void RoundResultsPage::setData(const game::RoundResults& roundResults, bool isGameOver)
{
    m_distanceMap->setActualLocation(roundResults.correctLocation);

    // TODO: [multiplayer] iterate over all players
    const game::PlayerRoundResult& playerResult = roundResults.playerResults.begin()->second;
    m_distanceMap->setGuessedLocation(playerResult.guess);
    m_distanceMap->setDistance(playerResult.distanceMeters);

    updateDistanceLabel(playerResult);
    updatePointsLabel(playerResult);

    if (isGameOver)
    {
        m_isGameOver = true;
        m_proceedButton->setText("Summary");
    }
}

void RoundResultsPage::setupLayout()
{
    setLayout(m_layout);
    m_layout->setContentsMargins(0, 0, 0, 0);
}

void RoundResultsPage::setupInfoLabels()
{
    m_layout->addWidget(m_distanceLabel, 0, Qt::AlignCenter);
    m_layout->addWidget(m_pointsLabel, 0, Qt::AlignCenter);

    m_distanceLabel->setFont(QFont{"Times New Roman", 20});
    m_pointsLabel->setFont(QFont{"Times New Roman", 20});
}

void RoundResultsPage::setupDistanceMap()
{
    m_layout->addWidget(m_distanceMap);
    m_distanceMap->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void RoundResultsPage::setupContinueButton()
{
    m_layout->addWidget(m_proceedButton, 0, Qt::AlignCenter);
    m_proceedButton->setMinimumSize(100, 40);

    connect(m_proceedButton, &QPushButton::clicked, this, &RoundResultsPage::onProceedButtonClicked);
}

void RoundResultsPage::setupBottomSpacing()
{
    m_layout->addSpacing(10);
}

void RoundResultsPage::onProceedButtonClicked()
{
    if (m_isGameOver)
    {
        emit summaryRequested();
    }
    else
    {
        emit nextRoundRequested();
    }
}

void RoundResultsPage::updateDistanceLabel(const game::PlayerRoundResult& result)
{
    std::ostringstream formatter;
    formatter << "Your guess was ";
    formatter << std::fixed << std::setprecision(2);

    if (result.distanceMeters > 1000)
        formatter << result.distanceMeters / 1000 << " km";
    else
        formatter << result.distanceMeters << " m";

    formatter << " from the actual location.";

    m_distanceLabel->setText(formatter.str().c_str());
}

void RoundResultsPage::updatePointsLabel(const game::PlayerRoundResult& result)
{
    std::string pointsText = "Points: ";
    pointsText += std::to_string(result.points);

    m_pointsLabel->setText(pointsText.c_str());
}

// ReSharper restore CppMemberFunctionMayBeConst

}
