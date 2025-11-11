#include "game/pages/round_results.h"
#include "game/results.h"

namespace game::pages
{

RoundResultsPage::RoundResultsPage(QWidget* parent, const geo::Location& mapCenter)
    : QFrame(parent)
    , m_layout(this)
    , m_distanceMap(this, mapCenter)
{
    setLayout(&m_layout);
    m_layout.setContentsMargins(0, 0, 0, 0);
    m_layout.addWidget(&m_resultLabel);
    m_layout.addWidget(&m_distanceMap);

    m_resultLabel.setFont(QFont{"Times New Roman", 20});
    m_resultLabel.setAlignment(Qt::AlignCenter);
    m_distanceMap.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void RoundResultsPage::setActualLocation(const geo::Location& location)
{
    m_distanceMap.setActualLocation(location);
}

void RoundResultsPage::setGuessedLocation(const geo::Location& location)
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

}
