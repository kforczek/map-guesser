#pragma once
#include <qboxlayout.h>
#include <QLabel>
#include <QPushButton>

#include "ui/google/distance_map.h"

namespace game
{
class RoundResults;
}

namespace ui::pages
{

class RoundResultsPage final : public QFrame
{
    Q_OBJECT
public:
    explicit RoundResultsPage(QWidget* parent);

    void setActualLocation(const geo::Point& location);
    void setGuessedLocation(const geo::Point& location);
    void setInfo(const game::RoundResults& roundResults);

    void setCenter(const geo::Point& center);

signals:
    // TODO [naming] -> nextRoundRequested() etc
    void continueButtonClicked();

private /*members*/:
    QVBoxLayout m_layout;

    QLabel m_distanceLabel;
    QLabel m_pointsLabel;

    google::DistanceMap m_distanceMap;
    QPushButton m_continueButton;

private /*methods*/:
    void setupLayout();
    void setupInfoLabels();
    void setupDistanceMap();
    void setupContinueButton();
    void setupBottomSpacing();
    void addToLayout(QWidget& widget, Qt::Alignment alignment = Qt::Alignment());

    void onContinueButtonClicked();

    void updateDistanceLabel(const game::RoundResults& roundResults);
    void updatePointsLabel(const game::RoundResults& roundResults);
};

}
