#pragma once
#include <qboxlayout.h>
#include <QFrame>

#include "streetview/distance_map.h"

namespace game::pages
{

class RoundResultsPage : public QFrame
{
    Q_OBJECT
public:
    explicit RoundResultsPage(QWidget* parent);

    void setActualLocation(const geo::Location& location);
    void setGuessedLocation(const geo::Location& location);

private:
    QVBoxLayout m_layout;
    sv::DistanceMap m_distanceMap;
};

}
