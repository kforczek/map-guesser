#include "app/ui/widgets/propedit/map_path.h"
#include "app/ui/map_file_selector.h"

namespace app::ui::widgets::propedit
{

MapPathPropertyEditor::MapPathPropertyEditor(QWidget* parent)
    : PropertyEditor(parent, "Map")
    , m_valueEdit(this)
    , m_browseButton("Browse...", this)
{
    addToLayout(m_valueEdit);
    addToLayout(m_browseButton);

    connect(&m_browseButton, &QPushButton::clicked, this, &MapPathPropertyEditor::onBrowseButtonClicked);
}

QString MapPathPropertyEditor::getValue() const
{
    return m_valueEdit.text();
}

void MapPathPropertyEditor::onBrowseButtonClicked()
{
    const QString browsedPath = GetOpenMapPath(this, m_valueEdit.text());
    m_valueEdit.setText(browsedPath);
}

}
