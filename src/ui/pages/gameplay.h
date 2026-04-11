#pragma once
#include <QFrame>
#include <QTime>
#include "geo/point.h"

class QLabel;
class QPushButton;

namespace ui::google
{
class StreetView;
class InteractiveMap;
}

namespace ui::widgets
{
class GameplayRoundInfoBox;
}

namespace ui::pages
{

class GameplayPage final : public QFrame
{
    Q_OBJECT
public:
    explicit GameplayPage(QWidget* parent);

    const geo::Point& getStreetViewLocation() const;

    void prepareNewGame(unsigned int roundsCnt, QTime roundTimeLimit);
    void startNextRound(const geo::Point& location);

    void setMapCenter(const geo::Point& center);

signals:
    void playerFinishedRound(const std::optional<geo::Point>& location);

protected:
    void showEvent(QShowEvent *event) override;
    void resizeEvent(QResizeEvent* event) override;

private /*fields*/:
    bool m_initialized = false;

    google::StreetView* m_streetView = nullptr;
    google::InteractiveMap* m_interactiveMap = nullptr;

    unsigned int m_currRoundNumber = 0;
    unsigned int m_currRoundTimeLeft = 0;

    unsigned int m_roundsCnt = 0;
    unsigned int m_roundTimeLimit = 0;

    QTimer* m_roundTimer = nullptr;

    QWidget* m_leftInfoBox = nullptr;
    QLabel* m_roundInfoLabel = nullptr;
    QLabel* m_timerInfoLabel = nullptr;

    QPushButton* m_returnToStartButton = nullptr;
    QPushButton* m_guessButton = nullptr;

    QPushButton* m_shrinkMapButton = nullptr;
    QPushButton* m_enlargeMapButton = nullptr;

    double m_mapToWindowWidthRatio = 0;
    geo::Point m_mapCenter;

private /*methods*/:
    void ensureInitialized();

    void setupMembers();
    void setupGeometries();
    void setupConnections();

    void resize();
    void resizeStreetView();
    void resizeAndMoveMap(int newWidth = 0, int newHeight = 0);
    void moveMapSizeButtons();
    void moveFunctionalButtons();

    void updateMapRatios();
    void setMapSizeButtonsEnabledState();
    void setTimerLabelUrgency(const QString& urgency);

private slots:
    void onGuessMarkerPlaced();
    void onTimerTick();

    void onGuessButtonClicked();
    void onReturnToStartButtonClicked();

    void onShrinkMapButtonClicked();
    void onEnlargeMapButtonClicked();
};

}
