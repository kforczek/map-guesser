#include "app/ui/widgets/propedit/base.h"

namespace app::ui::widgets::propedit
{

PropertyEditor::PropertyEditor(QWidget* parent, const QString& propertyName)
    : QWidget(parent)
    , m_layout(this)
    , m_label(propertyName, this)
{
    setLayout(&m_layout);
    m_layout.addWidget(&m_label);
}

void PropertyEditor::addToLayout(QWidget& widget)
{
    m_layout.addWidget(&widget);
}

}