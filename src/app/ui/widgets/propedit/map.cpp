#include "app/ui/map_file_access.h"
#include "app/ui/widgets/propedit/map.h"
#include "app/ui/map_file_selector.h"

namespace app::ui::widgets::propedit
{

MapPropertyEditor::MapPropertyEditor(QWidget* parent)
    : PropertyEditor(parent, "Map")
    , m_valueEdit(this)
    , m_browseButton("Browse...", this)
{
    m_valueEdit.setMinimumWidth(500);

    connect(&m_browseButton, &QPushButton::clicked, this, &MapPropertyEditor::onBrowseButtonClicked);

    addToLayout(m_valueEdit, 1, Qt::Alignment{});
    addToLayout(m_browseButton, 0, Qt::Alignment{});
    finishInit();
}

geo::Map MapPropertyEditor::getValue() const
{
    const QString mapPath = m_valueEdit.text();
    return app::ui::LoadMapFromFile(mapPath);
}

void MapPropertyEditor::onBrowseButtonClicked()
{
    const QString browsedPath = GetOpenMapPath(this, m_valueEdit.text());
    m_valueEdit.setText(browsedPath);
}

}
