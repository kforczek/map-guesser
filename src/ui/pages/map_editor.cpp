#include "ui/pages/map_editor.h"

#include <QFile>
#include <QMessageBox>

#include "ui/mapfile/access.h"
#include "ui/mapfile/selector.h"

namespace ui::pages
{

MapEditorPage::MapEditorPage(QWidget* parent, api_usage::Counter& apiUsageCounter)
    : QFrame(parent)
    , m_apiUsageCounter(&apiUsageCounter) { }

void MapEditorPage::preparePage()
{
    const bool topBarExists = m_topBar != nullptr;
    const bool mapViewExists = m_mapView != nullptr;
    assert(topBarExists == mapViewExists);

    if (topBarExists && mapViewExists)
        return;

    m_topBar = new widgets::MapEditorTopBar(this);
    m_mapView = new google::PolygonMap(this, *m_apiUsageCounter);

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

    if (QString filePath = mapfile::GetOpenMapPath(this, startPath); !filePath.isEmpty())
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

    QString filePath = mapfile::GetSaveMapPath(this, startPath);
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
    catch (mapfile::AccessError& err)
    {
        QMessageBox::critical(this, "Load error", err.what());
    }
}

void MapEditorPage::tryLoadMap(QString filePath)
{
    m_mapData = mapfile::LoadFromFile(filePath);
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
    catch (mapfile::AccessError& err)
    {
        QMessageBox::critical(this, "Save error", err.what());
    }
}

void MapEditorPage::trySaveMap() const
{
    assert(m_mapData);
    assert(m_mapFilePath);

    mapfile::SaveToFile(*m_mapData, *m_mapFilePath);
}

}
