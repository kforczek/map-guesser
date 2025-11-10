#pragma once
#include <QMainWindow>
#include <QPushButton>

#include "streetview/distance_map.h"
#include "streetview/interactive_map.h"
#include "streetview/streetview.h"

namespace game
{

class GameWindow : public QMainWindow
{
    Q_OBJECT
public:
    GameWindow(const geo::Location& mapStartLocation);

    void setLocation(geo::Location location);

private:
    sv::StreetView m_streetView;
    sv::InteractiveMap m_interactiveMap;
    sv::DistanceMap m_distanceMap;

    QPushButton m_guessButton;

    geo::Location m_currLocation{0, 0};

private slots:
    void onGuessButtonClicked();
};

}
