#include <QApplication>
#include <QWebEngineView>
#include <QWebEngineSettings>
#include <QWebEngineProfile>
#include <QUrl>
#include <QDebug>
#include <QLoggingCategory>
#include <filesystem>

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
    
    QWebEngineView view;
    view.resize(1024, 768);

    // Enable all performance-related settings
    auto settings = view.settings();
    settings->setAttribute(QWebEngineSettings::WebGLEnabled, true);
    settings->setAttribute(QWebEngineSettings::Accelerated2dCanvasEnabled, true);
    settings->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
    settings->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);
    settings->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    settings->setAttribute(QWebEngineSettings::AllowRunningInsecureContent, false);
    
    // Enable smooth scrolling
    settings->setAttribute(QWebEngineSettings::ScrollAnimatorEnabled, true);
    
    // Use system locale
    settings->setAttribute(QWebEngineSettings::LocalStorageEnabled, true);

    qDebug() << "Loading URL: http://localhost:8000/streetview.html";
    
    // Load the URL
    QUrl url("http://localhost:8000/streetview.html");
    view.setUrl(url);

    // Connect to loadFinished signal
    QObject::connect(&view, &QWebEngineView::loadFinished, [](bool success) {
        if (success) {
            qDebug() << "Page loaded successfully!";
        } else {
            qDebug() << "Page failed to load!";
        }
    });

    view.show();
    return app.exec();
}