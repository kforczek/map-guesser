#include <QApplication>
#include <QWebEngineView>
#include <QWebEngineSettings>
#include <QWebEngineProfile>
#include <QUrl>
#include <QDebug>
#include <QLoggingCategory>
#include <QFile>
#include <filesystem>

#include "./src/streetview/streetview.h"
#include "src/common/location.h"

int main(int argc, char *argv[]) {
    // IMPORTANT: Set these BEFORE creating QApplication
    // Enable hardware acceleration and GPU features
    qputenv("QT_XCB_GL_INTEGRATION", "xcb_egl");
    qputenv("QTWEBENGINE_CHROMIUM_FLAGS", 
            "--enable-gpu "
            "--enable-features=VaapiVideoDecoder "
            "--ignore-gpu-blocklist "
            "--enable-accelerated-2d-canvas "
            "--enable-accelerated-video-decode "
            "--enable-gpu-rasterization "
            "--disable-gpu-driver-bug-workarounds "
            "--num-raster-threads=4");
    
    // Disable verbose Qt plugin loading messages
    QLoggingCategory::setFilterRules("qt.core.plugin.factoryloader=false\n"
                                     "qt.core.plugin.loader=false\n"
                                     "qt.core.library=false");

    QApplication app(argc, argv);
    
    sv::StreetView view;

    // TODO location randomization
    view.setLocation(Location{});
    view.show();

    return app.exec();
}
