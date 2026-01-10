#pragma once
#include <qboxlayout.h>
#include <QFrame>

#include "ui/google/polygon_map.h"
#include "ui/widgets/map_editor_top_bar.h"

namespace ui::pages
{

class MapEditorPage final : public QFrame
{
    Q_OBJECT
public:
    explicit MapEditorPage(QWidget* parent);

signals:
    void closePage();

private /*fields*/:
    widgets::MapEditorTopBar* m_topBar = nullptr;
    google::PolygonMap* m_mapView = nullptr;

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
