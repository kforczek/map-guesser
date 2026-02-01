#pragma once
#include <qboxlayout.h>
#include <QLabel>
#include <QPushButton>

#include "ui/google/distance_map.h"

namespace game
{
struct RoundResults;
struct PlayerRoundResult;
}

namespace ui::pages
{

class RoundResultsPage final : public QFrame
{
    Q_OBJECT
public:
    explicit RoundResultsPage(QWidget* parent);

    void setCenter(const geo::Point& center);
    void setData(const game::RoundResults& roundResults, bool isGameOver);

signals:
    void nextRoundRequested();
    void summaryRequested();

private /*members*/:
    QVBoxLayout* m_layout = nullptr;
    bool m_isGameOver = false;

    QLabel* m_distanceLabel = nullptr;
    QLabel* m_pointsLabel = nullptr;

    google::DistanceMap* m_distanceMap = nullptr;
    QPushButton* m_proceedButton = nullptr;

private /*methods*/:
    void setupLayout();
    void setupInfoLabels();
    void setupDistanceMap();
    void setupContinueButton();
    void setupBottomSpacing();

    void onProceedButtonClicked();

    void updateDistanceLabel(const game::PlayerRoundResult& result);
    void updatePointsLabel(const game::PlayerRoundResult& result);
};

}
