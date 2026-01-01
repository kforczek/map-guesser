#include <QApplication>
#include <QWebEngineSettings>
#include <QLoggingCategory>

#include "app/main_window.h"
#include "geo/point.h"

namespace
{

void initQtFlags()
{
    qputenv("QTWEBENGINE_CHROMIUM_FLAGS",
            "--enable-gpu "
            "--enable-features=VaapiVideoDecoder "
            "--ignore-gpu-blocklist "
            "--enable-accelerated-2d-canvas "
            "--enable-accelerated-video-decode "
            "--enable-gpu-rasterization ");

    QLoggingCategory::setFilterRules("qt.core.plugin.factoryloader=false\n"
                                     "qt.core.plugin.loader=false\n"
                                     "qt.core.library=false");
}

}

int main(int argc, char *argv[])
{
    initQtFlags();
    QApplication qAppInst{argc, argv};

    // TODO: check for active token during setup (before game), maybe validate the token somehow
    app::MainWindow window{};
    window.showFullScreen();

    return qAppInst.exec();
}
