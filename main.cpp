#include <QApplication>
#include <QWebEngineSettings>
#include <QLoggingCategory>

#include "db/location_pool.h"
#include "include/game/randomizer.h"
#include "include/geo/location.h"
#include "include/streetview/interactive_map.h"
#include "streetview/streetview.h"

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

int main(int argc, char *argv[]) {
    initQtFlags();
    QApplication app(argc, argv);
    
    // sv::StreetView view;
    //
    // // TODO location randomization
    // geo::Location streetViewPoint = game::GetRandomStreetViewPoint(db::LocationPool{});
    // view.setLocation(streetViewPoint);
    // view.show();

    auto* test = new sv::InteractiveMap(nullptr, geo::Location{50.0874, 14.4207});
    test->show();

    return app.exec();
}
