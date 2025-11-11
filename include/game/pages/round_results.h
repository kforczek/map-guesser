#pragma once
#include <qboxlayout.h>
#include <QFrame>
#include <QLabel>

#include "streetview/distance_map.h"

namespace game::pages
{

struct SResults
{
    double distanceMeters = 0;
    size_t points = 0;
};

class RoundResultsPage : public QFrame
{
    Q_OBJECT
public:
    explicit RoundResultsPage(QWidget* parent);

    void setActualLocation(const geo::Location& location);
    void setGuessedLocation(const geo::Location& location);
    void setInfo(const SResults& result);

private:
    QVBoxLayout m_layout;
    QLabel m_resultLabel;
    sv::DistanceMap m_distanceMap;
};

}
