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
    m_layout.addWidget(&m_distanceMap);
}

void RoundResultsPage::setActualLocation(const geo::Location& location)
{
    m_distanceMap.setActualLocation(location);
}

void RoundResultsPage::setGuessedLocation(const geo::Location& location)
{
    m_distanceMap.setGuessedLocation(location);
}

}