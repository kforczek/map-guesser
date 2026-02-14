#pragma once
#include <qboxlayout.h>
#include <QLabel>
#include <QPushButton>

namespace geo
{
class Point;
}

namespace game
{
struct RoundResults;
struct PlayerRoundResult;
}

namespace ui::google
{
class DistanceMap;
}

namespace ui::pages
{

class RoundResultsPage final : public QFrame
{
    Q_OBJECT
public /*helpers*/:
    enum class EContinueButtonType {
        NextRound,
        Summary
    };

public /*methods*/:
    explicit RoundResultsPage(QWidget* parent);

    void setCenter(const geo::Point& center);
    void setData(const game::RoundResults& roundResults);
    void setContinueButtonType(EContinueButtonType type);

/*public*/ signals:
    void closePage();

private /*members*/:
    QVBoxLayout* m_layout = nullptr;

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
