#include "ui/widgets/propedit/base.h"

namespace ui::widgets::propedit
{

PropertyEditor::PropertyEditor(QWidget* parent, const QString& propertyName)
    : QWidget(parent)
    , m_layout(this)
    , m_label(propertyName, this)
{
    setLayout(&m_layout);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

    m_layout.addStretch(1);
    m_layout.addWidget(&m_label, 0, Qt::AlignRight);
}

void PropertyEditor::addToLayout(QWidget& widget, int stretch /*= 1*/, Qt::Alignment alignment /*= Qt::AlignLeft*/)
{
    m_layout.addWidget(&widget, stretch, alignment);
}

void PropertyEditor::finishInit()
{
    m_layout.addStretch(1);
}

}