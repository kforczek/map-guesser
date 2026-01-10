#include "ui/widgets/map_editor_top_bar.h"

namespace ui::widgets
{

MapEditorTopBar::MapEditorTopBar(QWidget* parent)
    : QWidget(parent)
    , m_infoLabel(new QLabel(this))
    , m_loadButton(new QPushButton("Load", this))
    , m_saveButton(new QPushButton("Save", this))
    , m_saveAsButton(new QPushButton("Save As...", this))
{
    auto* layout = new QHBoxLayout(this);
    setLayout(layout);

    setupInfoLabel();
    setupLoadButton();
    setupSaveButton();
    setupSaveAsButton();
    setupSpacer();
    setupCloseButton();
}

void MapEditorTopBar::setSaveEnabled(bool enabled)
{
    m_saveButton->setEnabled(enabled);
    m_saveAsButton->setEnabled(enabled);
}

void MapEditorTopBar::setMapDisplayPath(const QString& path)
{
    m_infoLabel->setText("Map: " + path);
}

void MapEditorTopBar::setupInfoLabel()
{
    layout()->addWidget(m_infoLabel);
    m_infoLabel->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
    setMapDisplayPath("Untitled");
}

void MapEditorTopBar::setupLoadButton()
{
    layout()->addWidget(m_loadButton);
    connect(m_loadButton, &QPushButton::clicked, this, &MapEditorTopBar::loadButtonClicked);
}

void MapEditorTopBar::setupSaveButton()
{
    layout()->addWidget(m_saveButton);
    m_saveButton->setEnabled(false);
    connect(m_saveButton, &QPushButton::clicked, this, &MapEditorTopBar::saveButtonClicked);
}

void MapEditorTopBar::setupSaveAsButton()
{
    layout()->addWidget(m_saveAsButton);
    m_saveAsButton->setEnabled(false);
    connect(m_saveAsButton, &QPushButton::clicked, this, &MapEditorTopBar::saveAsButtonClicked);
}

void MapEditorTopBar::setupSpacer()
{
    layout()->addItem(new QSpacerItem(50, 0));
}

void MapEditorTopBar::setupCloseButton()
{
    auto* closeButton = new QPushButton("Close", this);
    layout()->addWidget(closeButton);
    connect(closeButton, &QPushButton::clicked, this, &MapEditorTopBar::closeButtonClicked);
}

}