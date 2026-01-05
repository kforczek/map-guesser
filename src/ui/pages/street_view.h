#pragma once
#include <qboxlayout.h>
#include <QFrame>
#include <QPushButton>

#include "ui/google/interactive_map.h"
#include "ui/google/streetview.h"

namespace geo
{
class Point;
}

namespace ui::pages
{

class StreetViewPage final : public QFrame
{
    Q_OBJECT
public:
    explicit StreetViewPage(QWidget* parent);

    const geo::Point& getStreetViewLocation() const;
    void startNewRound(const geo::Point& location);

    void setCenter(const geo::Point& center);

signals:
    void guessMade(const geo::Point& location);

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
