#pragma once
#include <QObject>
#include <qtmetamacros.h>

namespace game
{
class MapGuesserGame;
}

namespace geo
{
class Point;
}

namespace ui
{

class MainWindow;

class Controller final : public QObject
{
    Q_OBJECT
public:
    explicit Controller(game::MapGuesserGame& logicLayer, MainWindow& mainWindow);
};

}