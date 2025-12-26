#include "game/pages/map_editor.h"

#include <QFile>
#include <QMessageBox>

#include "map/file_selector.h"

namespace
{

// ############################################################

struct MapFileError final : std::runtime_error
{
    using std::runtime_error::runtime_error;
};

// ############################################################

QJsonDocument openAsJson(const QString& filePath)
{
    QFile file{filePath};

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw MapFileError{file.errorString().toStdString()};

    const QByteArray data = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);

    if (parseError.error != QJsonParseError::NoError)
        throw MapFileError{parseError.errorString().toStdString()};

    return doc;
}

// ############################################################

}

namespace game::pages
{

MapEditorPage::MapEditorPage(QWidget* parent)
    : QFrame(parent)
    , m_topBar(this)
    , m_mapView(this)
{
    setLayout(&m_layout);

    m_layout.addWidget(&m_topBar);
    m_layout.addWidget(&m_mapView);

    connect(&m_mapView, &google::PolygonMap::mapChanged, this, &MapEditorPage::onMapChanged);
    connect(&m_topBar, &map::editor::TopBar::loadButtonClicked, this, &MapEditorPage::onLoadRequested);
    connect(&m_topBar, &map::editor::TopBar::saveButtonClicked, this, &MapEditorPage::onSaveRequested);
    connect(&m_topBar, &map::editor::TopBar::saveAsButtonClicked, this, &MapEditorPage::onSaveAsRequested);
}

void MapEditorPage::onMapChanged(util::Consumable<geo::Map> updatedMap)
{
    m_mapData = updatedMap.consume();
    m_topBar.setSaveEnabled(true);
}

void MapEditorPage::onLoadRequested()
{
    const QString& startPath = m_mapFilePath ? *m_mapFilePath : "";

    if (QString filePath = map::getOpenFilePath(this, startPath); !filePath.isEmpty())
        loadMap(std::move(filePath));
}

void MapEditorPage::onSaveRequested()
{
    if (m_mapFilePath)
    {
        saveMap(*m_mapFilePath);
    }
    else
    {
        onSaveAsRequested();
    }
}

void MapEditorPage::onSaveAsRequested()
{
    const QString& startPath = m_mapFilePath ? *m_mapFilePath : "";

    if (const QString filePath = map::getSaveFilePath(this, startPath); !filePath.isEmpty())
        saveMap(filePath);
}

void MapEditorPage::loadMap(QString filePath)
{
    try
    {
        tryLoadMap(std::move(filePath));
    }
    catch (MapFileError& err)
    {
        QMessageBox::critical(this, "Load error", err.what());
    }
}

void MapEditorPage::tryLoadMap(QString filePath)
{
    const QJsonDocument jsonDoc = openAsJson(filePath);

    m_mapData = geo::Map::fromJson(jsonDoc);
    m_mapFilePath = std::move(filePath);

    m_mapView.loadMap(*m_mapData);
    m_topBar.setSaveEnabled(true);
}

void MapEditorPage::saveMap(const QString& filePath)
{
    try
    {
        trySaveMap(filePath);
    }
    catch (MapFileError& err)
    {
        QMessageBox::critical(this, "Save error", err.what());
    }
}

void MapEditorPage::trySaveMap(const QString& filePath) const
{
    assert(m_mapData);
    const QJsonDocument jsonDoc = m_mapData->toJson();

    QFile file{filePath};
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        throw MapFileError{file.errorString().toStdString()};

    file.write(jsonDoc.toJson());
    file.close();
}

}
