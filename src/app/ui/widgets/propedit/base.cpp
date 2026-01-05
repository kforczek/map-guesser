#include "app/ui/widgets/propedit/base.h"

namespace app::ui::widgets::propedit
{

PropertyEditor::PropertyEditor(QWidget* parent, const QString& propertyName)
    : QWidget(parent)
    , m_layout(this)
    , m_label(propertyName, this)
{
    setLayout(&m_layout);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

    addToLayout(m_label, 0, Qt::AlignRight);
}

void PropertyEditor::addToLayout(QWidget& widget, int stretch /*= 0*/, Qt::Alignment alignment /*= Qt::AlignLeft*/)
{
    m_layout.addWidget(&widget, stretch, alignment);
}

}