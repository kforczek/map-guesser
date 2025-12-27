#include "map/editor/top_bar.h"

namespace map::editor
{

TopBar::TopBar(QWidget* parent)
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

void TopBar::setSaveEnabled(bool enabled)
{
    m_saveButton.setEnabled(enabled);
    m_saveAsButton.setEnabled(enabled);
}

void TopBar::setMapDisplayPath(const QString& path)
{
    m_infoLabel.setText("Map: " + path);
}

void TopBar::setupInfoLabel()
{
    m_layout.addWidget(&m_infoLabel);
    m_infoLabel.setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
    setMapDisplayPath("Untitled");
}

void TopBar::setupLoadButton()
{
    m_layout.addWidget(&m_loadButton);
    connect(&m_loadButton, &QPushButton::clicked, this, &TopBar::loadButtonClicked);
}

void TopBar::setupSaveButton()
{
    m_layout.addWidget(&m_saveButton);

    m_saveButton.setEnabled(false);
    connect(&m_saveButton, &QPushButton::clicked, this, &TopBar::saveButtonClicked);
}

void TopBar::setupSaveAsButton()
{
    m_layout.addWidget(&m_saveAsButton);
    m_saveAsButton.setEnabled(false);
    connect(&m_saveAsButton, &QPushButton::clicked, this, &TopBar::saveAsButtonClicked);
}

}