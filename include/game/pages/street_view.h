#pragma once
#include <qboxlayout.h>
#include <QFrame>
#include <QPushButton>

#include "google/interactive_map.h"
#include "google/streetview.h"

namespace geo
{
class Location;
}

namespace game::pages
{

class StreetViewPage final : public QFrame
{
    Q_OBJECT
public:
    explicit StreetViewPage(QWidget* parent, const geo::Location& mapCenter);

    const geo::Location& getStreetViewLocation() const;
    void startNewRound(const geo::Location& location);

signals:
    void guessMade(const geo::Location& location);

protected:
    void showEvent(QShowEvent *event) override;
    void resizeEvent(QResizeEvent* event) override;

private /*fields*/:
    google::StreetView m_streetView;
    google::InteractiveMap m_interactiveMap;

    QPushButton m_returnToStartButton;
    QPushButton m_guessButton;

    QPushButton m_shrinkMapButton;
    QPushButton m_enlargeMapButton;

    double m_mapToWindowWidthRatio = 0;

private /*methods*/:
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
