#include "html_reader.h"
#include "google/token.h"
#include <QFile>

namespace ui::google
{

QString ReadAndFillApiToken(const QString& path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        throw std::runtime_error("Failed to retrieve API token - unable to open file at " + path.toStdString());

    QString htmlTemplate = file.readAll();
    htmlTemplate.replace("__API_KEY__", ::google::LoadApiToken());

    return htmlTemplate;
}

}
