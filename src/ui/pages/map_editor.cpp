#include "ui/pages/map_editor.h"

#include <QFile>
#include <QMessageBox>

#include "ui/utils/map_file_access.h"
#include "ui/utils/map_file_selector.h"

namespace ui::pages
{

MapEditorPage::MapEditorPage(QWidget* parent)
    : QFrame(parent)
    , m_topBar(new widgets::MapEditorTopBar(this))
    , m_mapView(new google::PolygonMap(this))
{
    setLayout(new QVBoxLayout(this));

    layout()->addWidget(m_topBar);
    layout()->addWidget(m_mapView);

    connect(m_mapView, &google::PolygonMap::mapChanged, this, &MapEditorPage::onMapChanged);
    connect(m_topBar, &widgets::MapEditorTopBar::loadButtonClicked, this, &MapEditorPage::onLoadRequested);
    connect(m_topBar, &widgets::MapEditorTopBar::saveButtonClicked, this, &MapEditorPage::onSaveRequested);
    connect(m_topBar, &widgets::MapEditorTopBar::saveAsButtonClicked, this, &MapEditorPage::onSaveAsRequested);
    connect(m_topBar, &widgets::MapEditorTopBar::closeButtonClicked, this, &MapEditorPage::closePage);
}

void MapEditorPage::onMapChanged(util::Consumable<geo::Map> updatedMap)
{
    m_mapData = updatedMap.consume();
    m_topBar->setSaveEnabled(true);
}

void MapEditorPage::onLoadRequested()
{
    const QString& startPath = m_mapFilePath ? *m_mapFilePath : "";

    if (QString filePath = utils::GetOpenMapPath(this, startPath); !filePath.isEmpty())
        loadMap(std::move(filePath));
}

void MapEditorPage::onSaveRequested()
{
    if (m_mapFilePath)
    {
        saveMap();
    }
    else
    {
        onSaveAsRequested();
    }
}

void MapEditorPage::onSaveAsRequested()
{
    const QString& startPath = m_mapFilePath ? *m_mapFilePath : "";

    QString filePath = utils::GetSaveMapPath(this, startPath);
    if (filePath.isEmpty())
        return;

    m_mapFilePath = std::move(filePath);
    m_topBar->setMapDisplayPath(*m_mapFilePath);
    saveMap();
}

void MapEditorPage::loadMap(QString filePath)
{
    try
    {
        tryLoadMap(std::move(filePath));
    }
    catch (utils::MapFileAccessError& err)
    {
        QMessageBox::critical(this, "Load error", err.what());
    }
}

void MapEditorPage::tryLoadMap(QString filePath)
{
    m_mapData = utils::LoadMapFromFile(filePath);
    m_mapFilePath = std::move(filePath);

    m_mapView->loadMap(*m_mapData);

    m_topBar->setMapDisplayPath(*m_mapFilePath);
    m_topBar->setSaveEnabled(true);
}

void MapEditorPage::saveMap()
{
    try
    {
        trySaveMap();
    }
    catch (utils::MapFileAccessError& err)
    {
        QMessageBox::critical(this, "Save error", err.what());
    }
}

void MapEditorPage::trySaveMap() const
{
    assert(m_mapData);
    assert(m_mapFilePath);

    utils::SaveMapToFile(*m_mapData, *m_mapFilePath);
}

}
