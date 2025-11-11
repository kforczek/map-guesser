#pragma once
#include <qboxlayout.h>
#include <QFrame>
#include <QLabel>

#include "streetview/distance_map.h"

namespace game
{
class RoundResults;
}

namespace game::pages
{

class RoundResultsPage : public QFrame
{
    Q_OBJECT
public:
    explicit RoundResultsPage(QWidget* parent, const geo::Location& mapCenter);

    void setActualLocation(const geo::Location& location);
    void setGuessedLocation(const geo::Location& location);
    void setInfo(const RoundResults& roundResults);

private:
    QVBoxLayout m_layout;
    QLabel m_resultLabel;
    sv::DistanceMap m_distanceMap;
};

}
