#include "google/html_reader.h"
#include "google/token.h"
#include <QFile>

namespace google
{

QString ReadAndFillApiToken(const QString& path)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly);

    QString htmlTemplate = file.readAll();
    htmlTemplate.replace("__API_KEY__", google::LoadApiToken());

    return htmlTemplate;
}

}
