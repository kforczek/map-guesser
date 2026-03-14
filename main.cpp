#include <QApplication>
#include <QFile>
#include <QLoggingCategory>
#include <QStandardPaths>

#include "game/game.h"
#include "ui/main_window.h"
#include "ui/bridge/connection.h"
#include "user/dir.h"
#include "user/settings.h"

namespace
{

// #################################################################

const char* WEB_ENGINE_VAR_NAME = "QTWEBENGINE_CHROMIUM_FLAGS";
const char* WEB_ENGINE_FLAGS =
    "--enable-gpu "
    "--enable-features=VaapiVideoDecoder "
    "--ignore-gpu-blocklist "
    "--enable-accelerated-2d-canvas "
    "--enable-accelerated-video-decode "
    "--enable-gpu-rasterization ";

const char* FILTER_RULES =
    "qt.core.plugin.factoryloader=false\n"
    "qt.core.plugin.loader=false\n"
    "qt.core.library=false";

// #################################################################

QString getStyleSheet()
{
    QFile file{"./styles/dark_blue.qss"};
    if (!file.exists())
        return QString{};

    file.open(QIODevice::ReadOnly);
    return file.readAll();
}

// #################################################################

}

int main(int argc, char *argv[])
{
    qputenv(WEB_ENGINE_VAR_NAME, WEB_ENGINE_FLAGS);
    QLoggingCategory::setFilterRules(FILTER_RULES);
    QCoreApplication::setApplicationName("MapGuesser");

    QApplication app{argc, argv};

    app.setStyleSheet(getStyleSheet());

    const QString userDirPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    user::SetUserDirPath(userDirPath.toStdString());

    user::settings::Load();

    // TODO: check for active token during setup (before game), maybe validate the token somehow
    game::MapGuesserGame mapGuesser;
    ui::MainWindow mainWindow;

    ui::bridge::Connect(mapGuesser, mainWindow);
    mainWindow.showFullScreen();

    return QApplication::exec();
}
