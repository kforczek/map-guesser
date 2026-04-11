#include "player_data.h"
#include <QStringList>

namespace
{
using namespace ui::cache;

std::vector<PlayerData> id2playerData;
}

namespace ui::cache
{

const std::vector<PlayerData>& GetId2PlayerData()
{
    return id2playerData;
}

void ResetPlayerData(const QStringList& playerNames)
{
    id2playerData.clear();
    id2playerData.reserve(playerNames.size());

    for (const auto& name : playerNames)
    {
        id2playerData.emplace_back(PlayerData{name});
    }
}

}