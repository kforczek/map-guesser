#include "game/pages/round_results.h"

namespace game::pages
{

RoundResultsPage::RoundResultsPage(QWidget* parent)
    : QFrame(parent)
    , m_layout(this)
    , m_distanceMap(this)
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

void RoundResultsPage::setInfo(const SResults& result)
{
    std::ostringstream formatter;
    formatter << "Your guess was ";
    formatter << std::fixed << std::setprecision(2);

    if (result.distanceMeters > 1000)
        formatter << result.distanceMeters / 1000 << " km";
    else
        formatter << result.distanceMeters << " m";

    formatter << " from the actual location.";

    // TODO: points
    m_resultLabel.setText(formatter.str().c_str());
}

}