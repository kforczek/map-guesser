#pragma once
#include <qboxlayout.h>
#include <QFrame>

#include "google/polygon_map.h"
#include "map/editor/top_bar.h"

namespace game::pages
{

class MapEditorPage final : public QFrame
{
    Q_OBJECT
public:
    explicit MapEditorPage(QWidget* parent);

private /*fields*/:
    QVBoxLayout m_layout;

    map::editor::TopBar m_topBar;
    google::PolygonMap m_mapView;

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

    void saveMap(const QString& filePath);
    void trySaveMap(const QString& filePath) const;
};

}
