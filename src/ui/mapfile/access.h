#pragma once
#include <filesystem>
#include <stdexcept>

#include "geo/map.h"

class QString;
class QJsonDocument;

// TODO: top-level module (dll) mapfile (?)
namespace ui::mapfile
{

geo::Map LoadFromFile(const QString& path);
geo::Map FromJson(const QJsonDocument& jsonDoc);

void SaveToFile(const geo::Map& map, const QString& path);
QJsonDocument ToJson(const geo::Map& map);

// #####################################################

struct AccessError final : std::runtime_error
{
    using std::runtime_error::runtime_error;
};

}
