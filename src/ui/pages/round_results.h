#pragma once
#include <qboxlayout.h>
#include <QLabel>
#include <QPushButton>
#include "geo/point.h"

namespace ui::api_usage
{
class Counter;
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
    explicit RoundResultsPage(QWidget* parent, api_usage::Counter& apiUsageCounter);

    void setCenter(const geo::Point& center);
    void setData(const game::RoundResults& roundResults);
    void setContinueButtonType(EContinueButtonType type);

/*public*/ signals:
    void ghostWalkRequested();
    void closePage();

private /*members*/:
    bool m_initialized = false;
    QVBoxLayout* m_layout = nullptr;

    api_usage::Counter* m_apiUsageCounter = nullptr;

    QLabel* m_distanceLabel = nullptr;
    QLabel* m_pointsLabel = nullptr;

    google::DistanceMap* m_distanceMap = nullptr;
    QPushButton* m_proceedButton = nullptr;

    geo::Point m_mapCenter;

private /*methods*/:
    void ensureInitialized();
    void setupLayout();
    void setupInfoLabels();
    void setupDistanceMap();
    void setupBottomButtons();
    void setupBottomSpacing();

    void onProceedButtonClicked();

    void updateDistanceLabel(const game::PlayerRoundResult& result);
    void updatePointsLabel(const game::PlayerRoundResult& result);
};

}
