#pragma once
#include <QString>

class QWidget;

namespace app::ui
{

QString GetOpenMapPath(QWidget* parent, const QString& startPath = {});
QString GetSaveMapPath(QWidget* parent, const QString& startPath = {});

}
