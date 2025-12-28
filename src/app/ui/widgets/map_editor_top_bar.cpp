#include "app/ui/widgets/map_editor_top_bar.h"

namespace app::ui::widgets
{

MapEditorTopBar::MapEditorTopBar(QWidget* parent)
    : QWidget(parent)
    , m_layout(this)
    , m_infoLabel(this)
    , m_loadButton("Load", this)
    , m_saveButton("Save", this)
    , m_saveAsButton("Save As...", this)
{
    setLayout(&m_layout);

    setupInfoLabel();
    setupLoadButton();
    setupSaveButton();
    setupSaveAsButton();
}

void MapEditorTopBar::setSaveEnabled(bool enabled)
{
    m_saveButton.setEnabled(enabled);
    m_saveAsButton.setEnabled(enabled);
}

void MapEditorTopBar::setMapDisplayPath(const QString& path)
{
    m_infoLabel.setText("Map: " + path);
}

void MapEditorTopBar::setupInfoLabel()
{
    m_layout.addWidget(&m_infoLabel);
    m_infoLabel.setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
    setMapDisplayPath("Untitled");
}

void MapEditorTopBar::setupLoadButton()
{
    m_layout.addWidget(&m_loadButton);
    connect(&m_loadButton, &QPushButton::clicked, this, &MapEditorTopBar::loadButtonClicked);
}

void MapEditorTopBar::setupSaveButton()
{
    m_layout.addWidget(&m_saveButton);

    m_saveButton.setEnabled(false);
    connect(&m_saveButton, &QPushButton::clicked, this, &MapEditorTopBar::saveButtonClicked);
}

void MapEditorTopBar::setupSaveAsButton()
{
    m_layout.addWidget(&m_saveAsButton);
    m_saveAsButton.setEnabled(false);
    connect(&m_saveAsButton, &QPushButton::clicked, this, &MapEditorTopBar::saveAsButtonClicked);
}

}