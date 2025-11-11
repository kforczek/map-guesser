#pragma once
#include <qboxlayout.h>
#include <QFrame>
#include <QPushButton>

#include "streetview/interactive_map.h"
#include "streetview/streetview.h"

namespace geo
{
class Location;
}

namespace game::pages
{

class StreetViewPage : public QFrame
{
    Q_OBJECT
public:
    explicit StreetViewPage(QWidget* parent, const geo::Location& mapCenter);

    const geo::Location& getStreetViewLocation() const;
    void setStreetViewLocation(const geo::Location& location);

    void resetForNewRound();

    void resizeEvent(QResizeEvent* event) override;

signals:
    void guessMade(const geo::Location& location);

private:
    sv::StreetView m_streetView;
    sv::InteractiveMap m_interactiveMap;

    QPushButton m_guessButton;

private slots:
    void onGuessMarkerPlaced();
    void onGuessButtonClicked();
};

}
