#pragma once
#include <QString>
#include <vector>

namespace ui::cache
{

struct PlayerData
{
    QString name;
    int points = 0;
};

const std::vector<PlayerData>& GetId2PlayerData();
void ResetPlayerData(const QStringList& playerNames);

}
