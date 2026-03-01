#pragma once
#include <QFrame>
#include <QPushButton>
#include "geo/point.h"

namespace ui::google
{
class StreetView;
class InteractiveMap;
}

namespace ui::pages
{

class GameplayPage final : public QFrame
{
    Q_OBJECT
public:
    explicit GameplayPage(QWidget* parent);

    const geo::Point& getStreetViewLocation() const;
    void startNextRound(const geo::Point& location);

    void setMapCenter(const geo::Point& center);

signals:
    void guessMade(const geo::Point& location);

protected:
    void showEvent(QShowEvent *event) override;
    void resizeEvent(QResizeEvent* event) override;

private /*fields*/:
    bool m_initialized = false;
    google::StreetView* m_streetView = nullptr;
    google::InteractiveMap* m_interactiveMap = nullptr;

    QPushButton* m_returnToStartButton = nullptr;
    QPushButton* m_guessButton = nullptr;

    QPushButton* m_shrinkMapButton = nullptr;
    QPushButton* m_enlargeMapButton = nullptr;

    double m_mapToWindowWidthRatio = 0;
    geo::Point m_mapCenter;

private /*methods*/:
    void ensureInitialized();

    void resize();
    void resizeStreetView();
    void resizeAndMoveMap(int newWidth = 0, int newHeight = 0);
    void moveMapSizeButtons();
    void moveFunctionalButtons();

    void updateMapRatios();
    void setMapSizeButtonsEnabledState();

private slots:
    void onGuessMarkerPlaced();

    void onGuessButtonClicked();
    void onReturnToStartButtonClicked();

    void onShrinkMapButtonClicked();
    void onEnlargeMapButtonClicked();
};

}
