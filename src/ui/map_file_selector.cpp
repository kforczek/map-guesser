#include "ui/map_file_selector.h"
#include <QFileDialog>

namespace
{

const QString STR_CAPTION = "Select map file";
const QString STR_FILTER = "Map Guesser map files (*.mg) ;; All files (*)";

}

namespace ui
{

QString GetOpenMapPath(QWidget* parent /*= nullptr*/, const QString& startPath /*= {}*/)
{
    return QFileDialog::getOpenFileName(parent, STR_CAPTION, startPath, STR_FILTER);
}
QString GetSaveMapPath(QWidget* parent /*= nullptr*/, const QString& startPath /*= {}*/)
{
    QString filePath = QFileDialog::getSaveFileName(parent, STR_CAPTION, startPath, STR_FILTER);
    if (!std::filesystem::path{filePath.toStdString()}.has_extension())
        filePath += ".mg";

    return filePath;
}

}