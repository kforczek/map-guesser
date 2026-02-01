#pragma once

namespace game
{
class MapGuesserGame;
}

namespace ui
{
class MainWindow;
}

namespace ui::bridge
{

void Connect(game::MapGuesserGame& logicLayer, MainWindow& mainWindow);

}