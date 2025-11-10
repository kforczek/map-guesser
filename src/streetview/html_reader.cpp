#include "streetview/html_reader.h"
#include "streetview/token.h"
#include <QFile>

namespace sv
{

QString ReadAndFillApiToken(const QString& path)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly);

    QString htmlTemplate = file.readAll();
    htmlTemplate.replace("__API_KEY__", sv::LoadApiToken());

    return htmlTemplate;
}

}
