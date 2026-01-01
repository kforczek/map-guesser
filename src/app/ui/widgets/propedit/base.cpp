#include "app/ui/widgets/propedit/base.h"

namespace app::ui::widgets::propedit
{

PropertyEditor::PropertyEditor(QWidget* parent, const QString& propertyName)
    : QWidget(parent)
    , m_layout(this)
    , m_label(propertyName, this)
{
    setLayout(&m_layout);
    addToLayout(m_label, Qt::AlignRight);
}

void PropertyEditor::addToLayout(QWidget& widget, Qt::Alignment alignment /*= Qt::AlignLeft*/)
{
    m_layout.addWidget(&widget, 0, alignment);
}

}