#include <QMainWindow>

#include "streetview/interactive_map.h"
#include "streetview/streetview.h"

namespace game
{

class GameWindow : public QMainWindow
{
public:
    GameWindow(const geo::Location& mapStartLocation);

    void setLocation(const geo::Location& location);

private:
    sv::StreetView m_streetView;
    sv::InteractiveMap m_interactiveMap;
};

}
