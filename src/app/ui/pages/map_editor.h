#pragma once
#include <qboxlayout.h>
#include <QFrame>

#include "google/polygon_map.h"
#include "app/ui/widgets/map_editor_top_bar.h"

namespace app::ui::pages
{

class MapEditorPage final : public QFrame
{
    Q_OBJECT
public:
    explicit MapEditorPage(QWidget* parent);

signals:
    void closePage();

private /*fields*/:
    QVBoxLayout m_layout;

    widgets::MapEditorTopBar m_topBar;
    google::PolygonMap m_mapView;
    QPushButton m_closeButton; // TODO move me to top bar

    std::optional<geo::Map> m_mapData;
    std::optional<QString> m_mapFilePath;

    // TODO: Ctrl+S shortcut

private slots:
    void onMapChanged(util::Consumable<geo::Map> updatedMap);
    void onLoadRequested();
    void onSaveRequested();
    void onSaveAsRequested();

private /*methods*/:
    void loadMap(QString filePath);
    void tryLoadMap(QString filePath);

    void saveMap();
    void trySaveMap() const;
};

}
