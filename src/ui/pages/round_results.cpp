#include "ui/pages/round_results.h"
#include "game/round_results.h"
#include "ui/google/distance_map.h"

namespace
{

const QString BUTTON_TEXT_NEXT_ROUND = "Next Round";
const QString BUTTON_TEXT_SUMMARY = "Summary";

}

namespace ui::pages
{

// ReSharper disable CppMemberFunctionMayBeConst

RoundResultsPage::RoundResultsPage(QWidget* parent)
    : QFrame(parent) { }

void RoundResultsPage::setCenter(const geo::Point& center)
{
    m_mapCenter = center;

    if (m_distanceMap)
        m_distanceMap->setCenter(m_mapCenter);
}

void RoundResultsPage::setData(const game::RoundResults& roundResults)
{
    ensureInitialized();

    m_distanceMap->setActualLocation(roundResults.correctLocation);

    // TODO: [multiplayer] iterate over all players
    const game::PlayerRoundResult& playerResult = roundResults.playerResults.begin()->second;
    m_distanceMap->setGuessedLocation(playerResult.guess);
    m_distanceMap->setDistance(playerResult.distanceMeters.value_or(0));

    updateDistanceLabel(playerResult);
    updatePointsLabel(playerResult);
}

void RoundResultsPage::setContinueButtonType(EContinueButtonType type)
{
    ensureInitialized();

    if (type == EContinueButtonType::NextRound)
    {
        m_proceedButton->setText(BUTTON_TEXT_NEXT_ROUND);
    }
    else
    {
        m_proceedButton->setText(BUTTON_TEXT_SUMMARY);
    }
}

void RoundResultsPage::ensureInitialized()
{
    if (m_initialized)
        return;

    setupLayout();
    setupInfoLabels();
    setupDistanceMap();
    setupBottomButtons();
    setupBottomSpacing();

    m_initialized = true;
}

void RoundResultsPage::setupLayout()
{
    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);

    setLayout(m_layout);
}

void RoundResultsPage::setupInfoLabels()
{
    m_distanceLabel = new QLabel(this);
    m_pointsLabel = new QLabel(this);

    m_distanceLabel->setObjectName("resultDistance");
    m_pointsLabel->setObjectName("resultPoints");

    m_layout->addWidget(m_distanceLabel, 0, Qt::AlignCenter);
    m_layout->addWidget(m_pointsLabel, 0, Qt::AlignCenter);
}

void RoundResultsPage::setupDistanceMap()
{
    m_distanceMap = new google::DistanceMap(this);
    m_distanceMap->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    if (m_mapCenter != geo::Point{})
        m_distanceMap->setCenter(m_mapCenter);

    m_layout->addWidget(m_distanceMap);
}

void RoundResultsPage::setupBottomButtons()
{
    m_proceedButton = new QPushButton(BUTTON_TEXT_NEXT_ROUND, this);
    auto* ghostWalkButton = new QPushButton("Ghost Walk", this);

    m_proceedButton->setProperty("role", "mainAction");
    ghostWalkButton->setProperty("role", "secondaryAction");

    auto* leftWidget = new QWidget(this);
    auto* leftLayout = new QHBoxLayout(leftWidget);
    leftLayout->setContentsMargins(10, 0, 0, 0);
    leftLayout->addWidget(ghostWalkButton);
    leftLayout->addStretch();

    auto* bottomBarLayout = new QHBoxLayout;
    m_layout->addLayout(bottomBarLayout);

    bottomBarLayout->addWidget(leftWidget, 1);
    bottomBarLayout->addWidget(m_proceedButton, 0, Qt::AlignCenter);
    bottomBarLayout->addStretch(1);

    connect(m_proceedButton, &QPushButton::clicked, this, &RoundResultsPage::onProceedButtonClicked);
    connect(ghostWalkButton, &QPushButton::clicked, this, &RoundResultsPage::ghostWalkRequested);
}

void RoundResultsPage::setupBottomSpacing()
{
    m_layout->addSpacing(10);
}

void RoundResultsPage::onProceedButtonClicked()
{
    emit closePage();
}

void RoundResultsPage::updateDistanceLabel(const game::PlayerRoundResult& result)
{
    if (!result.distanceMeters)
    {
        m_distanceLabel->setText("No guess placed!");
        return;
    }

    std::ostringstream formatter;
    formatter << "Your guess was ";
    formatter << std::fixed << std::setprecision(2);

    if (*result.distanceMeters > 1000)
        formatter << *result.distanceMeters / 1000 << " km";
    else
        formatter << *result.distanceMeters << " m";

    formatter << " from the actual location.";

    m_distanceLabel->setText(formatter.str().c_str());
}

void RoundResultsPage::updatePointsLabel(const game::PlayerRoundResult& result)
{
    std::string pointsText = "Points: ";
    pointsText += std::to_string(result.distancePoints);

    m_pointsLabel->setText(pointsText.c_str());
}

// ReSharper restore CppMemberFunctionMayBeConst

}
