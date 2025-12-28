#include "app/ui/map_file_access.h"

#include <QFile>

namespace
{

// ############################################################

QJsonDocument openAsJson(const QString& filePath)
{
    QFile file{filePath};

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw app::ui::MapFileAccessError{file.errorString().toStdString()};

    const QByteArray data = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);

    if (parseError.error != QJsonParseError::NoError)
        throw app::ui::MapFileAccessError{parseError.errorString().toStdString()};

    return doc;
}

// ############################################################

}

namespace app::ui
{

geo::Map LoadMapFromFile(const QString& path)
{
    const QJsonDocument jsonDoc = openAsJson(path);
    return geo::Map::fromJson(jsonDoc);
}

void SaveMapToFile(const geo::Map& map, const QString& path)
{
    const QJsonDocument jsonDoc = map.toJson();

    QFile file{path};
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        throw MapFileAccessError{file.errorString().toStdString()};

    file.write(jsonDoc.toJson());
    file.close();
}

}