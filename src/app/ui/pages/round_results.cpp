#include "app/ui/pages/round_results.h"
#include "app/results.h"

namespace app::ui::pages
{

RoundResultsPage::RoundResultsPage(QWidget* parent)
    : QFrame(parent)
    , m_layout(this)
    , m_resultLabel(this)
    , m_distanceMap(this)
    , m_continueButton("Next Round", this) // TODO: "Next Round" or "Summary" if game has ended
{
    setupLayout();
    setupResultLabel();
    setupDistanceMap();
    setupContinueButton();
    setupBottomSpacing();
}

void RoundResultsPage::setActualLocation(const geo::Point& location)
{
    m_distanceMap.setActualLocation(location);
}

void RoundResultsPage::setGuessedLocation(const geo::Point& location)
{
    m_distanceMap.setGuessedLocation(location);
}

void RoundResultsPage::setInfo(const RoundResults& roundResults)
{
    m_distanceMap.setDistance(roundResults.distanceMeters());

    std::ostringstream formatter;
    formatter << "Your guess was ";
    formatter << std::fixed << std::setprecision(2);

    if (roundResults.distanceMeters() > 1000)
        formatter << roundResults.distanceMeters() / 1000 << " km";
    else
        formatter << roundResults.distanceMeters() << " m";

    formatter << " from the actual location.";

    // TODO: points
    m_resultLabel.setText(formatter.str().c_str());
}

void RoundResultsPage::setCenter(const geo::Point& center)
{
    m_distanceMap.setCenter(center);
}

void RoundResultsPage::setupLayout()
{
    setLayout(&m_layout);
    m_layout.setContentsMargins(0, 0, 0, 0);
}

void RoundResultsPage::setupResultLabel()
{
    addToLayout(m_resultLabel, Qt::AlignCenter);
    m_resultLabel.setFont(QFont{"Times New Roman", 20});
}

void RoundResultsPage::setupDistanceMap()
{
    addToLayout(m_distanceMap);
    m_distanceMap.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void RoundResultsPage::setupContinueButton()
{
    addToLayout(m_continueButton, Qt::AlignCenter);
    m_continueButton.setMinimumSize(100, 40);

    connect(&m_continueButton, &QPushButton::clicked, this, &RoundResultsPage::onContinueButtonClicked);
}

void RoundResultsPage::setupBottomSpacing()
{
    m_layout.addSpacing(10);
}

void RoundResultsPage::addToLayout(QWidget& widget, Qt::Alignment alignment /*= Qt::Alignment()*/)
{
    m_layout.addWidget(&widget, 0, alignment);
}

void RoundResultsPage::onContinueButtonClicked()
{
    emit continueButtonClicked();
}

}
