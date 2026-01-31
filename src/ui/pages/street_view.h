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
    void startNextRound(const geo::Point& location);

    void setCenter(const geo::Point& center);

signals:
    void guessMade(const geo::Point& location);

protected:
    void showEvent(QShowEvent *event) override;
    void resizeEvent(QResizeEvent* event) override;

private /*fields*/:
    google::StreetView* m_streetView = nullptr;
    google::InteractiveMap* m_interactiveMap = nullptr;

    QPushButton* m_returnToStartButton = nullptr;
    QPushButton* m_guessButton = nullptr;

    QPushButton* m_shrinkMapButton = nullptr;
    QPushButton* m_enlargeMapButton = nullptr;

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
