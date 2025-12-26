#pragma once
#include <QString>

class QWidget;

namespace map
{

QString getOpenFilePath(QWidget* parent, const QString& startPath = {});
QString getSaveFilePath(QWidget* parent, const QString& startPath = {});

}
