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
    , m_spacer(50, 0)
    , m_closeButton("Close", this)
{
    setLayout(&m_layout);

    setupInfoLabel();
    setupLoadButton();
    setupSaveButton();
    setupSaveAsButton();
    setupSpacer();
    setupCloseButton();
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

void MapEditorTopBar::setupSpacer()
{
    m_layout.addItem(&m_spacer);
}

void MapEditorTopBar::setupCloseButton()
{
    m_layout.addWidget(&m_closeButton);
    connect(&m_closeButton, &QPushButton::clicked, this, &MapEditorTopBar::closeButtonClicked);
}

}