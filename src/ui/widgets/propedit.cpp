#include "propedit.h"

#include <qboxlayout.h>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>

#include "ui/map_file_access.h"
#include "ui/map_file_selector.h"

namespace
{

void initEditor(QWidget& editor, const QString& editorName, QWidget& valueEdit)
{
    auto* layout = new QHBoxLayout(&editor);
    editor.setLayout(layout);
    editor.setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

    layout->addStretch();
    layout->addWidget(new QLabel(editorName, &editor));
    layout->addWidget(&valueEdit);
    layout->addStretch();
}

}

namespace ui::widgets
{

MapPropertyEditor::MapPropertyEditor(QWidget* parent)
    : QWidget(parent)
    , m_valueEdit(new QLineEdit(this))
{
    auto* browseButton = new QPushButton("Browse...", this);

    auto* editWidget = new QWidget(this);
    auto* editWidgetLayout = new QHBoxLayout(editWidget);
    editWidget->setLayout(editWidgetLayout);
    editWidgetLayout->addWidget(m_valueEdit, 1);
    editWidgetLayout->addWidget(browseButton);

    initEditor(*this, "Map:", *editWidget);

    m_valueEdit->setMinimumWidth(500);
    connect(browseButton, &QPushButton::clicked, this, &MapPropertyEditor::onBrowseButtonClicked);
}

geo::Map MapPropertyEditor::getValue() const
{
    const QString mapPath = m_valueEdit->text();
    return ui::LoadMapFromFile(mapPath);
}

void MapPropertyEditor::onBrowseButtonClicked()
{
    const QString browsedPath = ui::GetOpenMapPath(this, m_valueEdit->text());
    m_valueEdit->setText(browsedPath);
}

// ########################################################################################

PositiveNumberPropertyEditor::PositiveNumberPropertyEditor(QWidget* parent, const QString& propertyName, const Values& values)
    : QWidget(parent)
    , m_valueEdit(new QSpinBox(this))
{
    initEditor(*this, propertyName, *m_valueEdit);

    m_valueEdit->setMinimum(values.minValue);
    m_valueEdit->setMaximum(values.maxValue);
    m_valueEdit->setValue(values.initialValue);
}

unsigned int PositiveNumberPropertyEditor::getValue() const
{
    const int val = m_valueEdit->value();
    assert(val >= 0);

    return static_cast<unsigned int>(val);
}

}