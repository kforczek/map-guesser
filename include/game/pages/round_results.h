#pragma once
#include <qboxlayout.h>
#include <QFrame>
#include <QLabel>
#include <QPushButton>

#include "google/distance_map.h"

namespace game
{
class RoundResults;
}

namespace game::pages
{

class RoundResultsPage final : public QFrame
{
    Q_OBJECT
public:
    explicit RoundResultsPage(QWidget* parent, const geo::Point& mapCenter);

    void setActualLocation(const geo::Point& location);
    void setGuessedLocation(const geo::Point& location);
    void setInfo(const RoundResults& roundResults);

signals:
    void continueButtonClicked();

private /*members*/:
    QVBoxLayout m_layout;

    QLabel m_resultLabel;
    google::DistanceMap m_distanceMap;
    QPushButton m_continueButton;

private /*methods*/:
    void setupLayout();
    void setupResultLabel();
    void setupDistanceMap();
    void setupContinueButton();
    void setupBottomSpacing();
    void addToLayout(QWidget& widget, Qt::Alignment alignment = Qt::Alignment());

    void onContinueButtonClicked();
};

}
