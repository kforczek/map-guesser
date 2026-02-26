#pragma once
#include <QString>

class QWidget;

namespace ui::mapfile
{

QString GetOpenMapPath(QWidget* parent, const QString& startPath = {});
QString GetSaveMapPath(QWidget* parent, const QString& startPath = {});

}
